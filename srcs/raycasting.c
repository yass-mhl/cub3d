# include "cube3d.h"


int	**cast(t_scene *scene)
{
	(void) scene;
	return(NULL);
}



int	**raycast(int **worldMap, double posX, double posY, double dirX, double dirY, double planeX, double planeY)
{
	int **buffer;
	buffer = calloc(WINDOW_HEIGHT + 1, sizeof(int *));
	if (!buffer)
		return (NULL);
	int y = 0;
	while (y < WINDOW_HEIGHT)
	{
		buffer[y] = calloc(WINDOW_WIDTH + 1, sizeof(int));
		if (!buffer[y])
        fprintf(stderr, "Failed to allocate memory for buffer[%d]\n", y);
		y++;
	}
	int *texture[8];
	for(int i = 0; i < 8; i++) {
    texture[i] = (int*)malloc(texWidth * texHeight * sizeof(int));
	}

	for(int x = 0; x < texWidth; x++)
  	for(int y = 0; y < texHeight; y++)
  	{
		int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
		//int xcolor = x * 256 / texWidth;
		int ycolor = y * 256 / texHeight;
		int xycolor = y * 128 / texHeight + x * 128 / texWidth;
		texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
		texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
		texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
		texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
		texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
		texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
		texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
		texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
	}
	for(int x = 0; x < WINDOW_WIDTH; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double) WINDOW_WIDTH - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX*cameraX;
      double rayDirY = dirY + planeY*cameraX;

      //which box of the map we're in
      int mapX = (int) posX;
      int mapY = (int) posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }

      //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);


      int pitch = 100;

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2 + pitch;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2 + pitch;
      if(drawEnd >= WINDOW_HEIGHT) drawEnd = WINDOW_HEIGHT - 1;

      //texturing calculations
      int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if(side == 0) wallX = posY + perpWallDist * rayDirY;
      else          wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double) texWidth);
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - pitch - WINDOW_HEIGHT / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y < drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		// printf("drawStart = %d\n", drawStart);
		// printf("drawEnd = %d\n", drawEnd);
		// printf("WINDOW_HEIGHT = %d\n", WINDOW_HEIGHT);
		// printf("WINDOW_WIDTH = %d\n", WINDOW_WIDTH);
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        int color = texture[texNum][texHeight * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
		// printf("color = %d\n", color);
		// printf("y = %d\n", y);
		// printf("x = %d\n", x);
        buffer[y][x] = color;
		// printf("x = %d, y = %d, color = %d\n", x, y, color);
      }
    }
	// int i;
	// int j = 0;

	// i = 0;
	// while (buffer[i])
	// {
	// 	j = 0;
	// 	while (buffer[i][j])
	// 	{
	// 		printf("%d i : %d", buffer[i][j], i);
	// 		j++;
	// 	}
	// 	printf(".\n");
	// 	i++;
	// }
	return (buffer);
}