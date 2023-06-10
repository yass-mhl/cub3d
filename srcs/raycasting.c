# include "cube3d.h"

// Fonction pour allouer de la mémoire pour le buffer
int **allocateBuffer() 
{
    int **buffer;
    buffer = calloc(WINDOW_HEIGHT + 1, sizeof(int *));
    if (!buffer)
        return NULL;
    int y = 0;
    while (y < WINDOW_HEIGHT) {
        buffer[y] = calloc(WINDOW_WIDTH + 1, sizeof(int));
        memset(buffer[y], -1, WINDOW_WIDTH * sizeof(int));
        if (!buffer[y])
            fprintf(stderr, "Failed to allocate memory for buffer[%d]\n", y);
        y++;
    }
    return buffer;
}

// Fonction pour créer des textures
int **createTextures() 
{
    int **texture = malloc(8 * sizeof(int *));
    int i = 0;
    while (i < 8) {
        texture[i] = (int*)malloc(texWidth * texHeight * sizeof(int));
        i++;
    }
    return texture;
}

// Fonction pour peupler les textures
void populateTextures(int **texture) {
    int x = 0;
    while (x < texWidth) {
        int y = 0;
        while (y < texHeight) {
            int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
            int ycolor = y * 256 / texHeight;
            int xycolor = y * 128 / texHeight + x * 128 / texWidth;
            texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y);
            texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
            texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor;
            texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
            texture[4][texWidth * y + x] = 256 * xorcolor;
            texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16);
            texture[6][texWidth * y + x] = 65536 * ycolor;
            texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128;
            y++;
        }
        x++;
    }
}


// Fonction pour le lancer de rayon
void raycast(int **worldMap, int **buffer, int **texture, double posX, double posY, double dirX, double dirY, double planeX, double planeY) {
    int x = 0;
    while (x < WINDOW_WIDTH) {
        //calculate ray position and direction
        double cameraX = 2 * x / (double) WINDOW_WIDTH - 1; //x-coordinate in camera space
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        //which box of the map we're in
        int mapX = (int) posX;
        int mapY = (int) posY;

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        //length of ray from one x or y-side to next x or y-side
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?

        //calculate step and initial sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }
        //perform DDA
        while (hit == 0) {
            //jump to next map square, either in x-direction, or in y-direction
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else          perpWallDist = (sideDistY - deltaDistY);

        //Calculate height of line to draw on screen
        int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);

        int pitch = 0;

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2 + pitch;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2 + pitch;
        if (drawEnd >= WINDOW_HEIGHT) drawEnd = WINDOW_HEIGHT - 1;

        //texturing calculations
        int texNum;
        if (side == 0) {  // Est/Ouest
            if (stepX > 0) {
                texNum = 0; // Texture for East
            } else {
                texNum = 1; // Texture for West
            }
        } else {  // Nord/Sud
            if (stepY > 0) {
                texNum = 2; // Texture for South
            } else {
                texNum = 3; // Texture for North
            }
        }

        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if (side == 0) wallX = posY + perpWallDist * rayDirY;
        else          wallX = posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        //x coordinate on the texture
        int texX = (int)(wallX * (double) texWidth);
        if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
        if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

        // How much to increase the texture coordinate per screen pixel
        double step = 1.0 * texHeight / lineHeight;
        // Starting texture coordinate
        double texPos = (drawStart - pitch - WINDOW_HEIGHT / 2 + lineHeight / 2) * step;
        int y = drawStart;
        while (y < drawEnd) {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            int color = texture[texNum][texHeight * texY + texX];
            if (side == 1) color = (color >> 1) & 8355711; // Make color darker for y-sides
            buffer[y][x] = color;
            y++;
        }
        x++;
    }
}



// Fonction pour dessiner des pixels
void drawPixels(int **buffer, int **texture, int texNum, int lineHeight, int drawStart, int drawEnd, int texX)
{
    // How much to increase the texture coordinate per screen pixel
    double step = 1.0 * texHeight / lineHeight;
    // Starting texture coordinate
    double texPos = (drawStart - WINDOW_HEIGHT / 2 + lineHeight / 2) * step;
    int y = drawStart;
    while (y < drawEnd) 
    {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        int color = texture[texNum][texHeight * texY + texX];
        // Make color darker for y-sides
        buffer[y][x] = color;
        y++;
    }
}


// Fonction principale
int **raycasting(int **worldMap, double posX, double posY, double dirX, double dirY, double planeX, double planeY) {
    // Allocate memory for the screen buffer
    int **buffer = allocateBuffer();
    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory for screen buffer\n");
        return NULL;
    }

    // Create and populate textures
    int **texture = createTextures();
    if (!texture) {
        fprintf(stderr, "Failed to create textures\n");
        // Here we should also free the previously allocated buffer before returning
        freeBuffer(buffer);
        return NULL;
    }
    populateTextures(texture);

    // Perform ray casting
    raycast(worldMap, buffer, texture, posX, posY, dirX, dirY, planeX, planeY);

    // Clean up textures as they are no longer needed
    // Assuming we have a function for this
    freeTextures(texture);

    // Return the resulting screen buffer
    return buffer;
}



// int	**raycasting(int **worldMap, double posX, double posY, double dirX, double dirY, double planeX, double planeY)
// {
// 	int **buffer;
// 	buffer = calloc(WINDOW_HEIGHT + 1, sizeof(int *));
// 	if (!buffer)
// 		return (NULL);
// 	int y = 0;
// 	while (y < WINDOW_HEIGHT)
// 	{
// 		buffer[y] = calloc(WINDOW_WIDTH + 1, sizeof(int));
//     memset(buffer[y], -1, WINDOW_WIDTH * sizeof(int));
// 		if (!buffer[y])
//         fprintf(stderr, "Failed to allocate memory for buffer[%d]\n", y);
// 		y++;
// 	}
// 	int *texture[8];
// 	for(int i = 0; i < 8; i++) {
//     texture[i] = (int*)malloc(texWidth * texHeight * sizeof(int));
// 	}

// 	for(int x = 0; x < texWidth; x++)
//   	for(int y = 0; y < texHeight; y++)
//   	{
// 		int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
// 		//int xcolor = x * 256 / texWidth;
// 		int ycolor = y * 256 / texHeight;
// 		int xycolor = y * 128 / texHeight + x * 128 / texWidth;
// 		texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
// 		texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
// 		texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
// 		texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
// 		texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
// 		texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
// 		texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
// 		texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
// 	}
// 	for(int x = 0; x < WINDOW_WIDTH; x++)
//     {
//       //calculate ray position and direction
//       double cameraX = 2 * x / (double) WINDOW_WIDTH - 1; //x-coordinate in camera space
//       double rayDirX = dirX + planeX*cameraX;
//       double rayDirY = dirY + planeY*cameraX;

//       //which box of the map we're in
//       int mapX = (int) posX;
//       int mapY = (int) posY;

//       //length of ray from current position to next x or y-side
//       double sideDistX;
//       double sideDistY;

//       //length of ray from one x or y-side to next x or y-side
//       double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
//       double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//       double perpWallDist;

//       //what direction to step in x or y-direction (either +1 or -1)
//       int stepX;
//       int stepY;

//       int hit = 0; //was there a wall hit?
//       int side; //was a NS or a EW wall hit?

//       //calculate step and initial sideDist
//       if(rayDirX < 0)
//       {
//         stepX = -1;
//         sideDistX = (posX - mapX) * deltaDistX;
//       }
//       else
//       {
//         stepX = 1;
//         sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//       }
//       if(rayDirY < 0)
//       {
//         stepY = -1;
//         sideDistY = (posY - mapY) * deltaDistY;
//       }
//       else
//       {
//         stepY = 1;
//         sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//       }
//       //perform DDA
//       while (hit == 0)
//       {
//         //jump to next map square, either in x-direction, or in y-direction
//         if(sideDistX < sideDistY)
//         {
//           sideDistX += deltaDistX;
//           mapX += stepX;
//           side = 0;
//         }
//         else
//         {
//           sideDistY += deltaDistY;
//           mapY += stepY;
//           side = 1;
//         }
//         //Check if ray has hit a wall
//         if(worldMap[mapX][mapY] > 0) hit = 1;
//       }

//       //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
//       if(side == 0) perpWallDist = (sideDistX - deltaDistX);
//       else          perpWallDist = (sideDistY - deltaDistY);

//       //Calculate height of line to draw on screen
//       int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);


//       int pitch = 0;

//       //calculate lowest and highest pixel to fill in current stripe
//       int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2 + pitch;
//       if(drawStart < 0) drawStart = 0;
//       int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2 + pitch;
//       if(drawEnd >= WINDOW_HEIGHT) drawEnd = WINDOW_HEIGHT;

//       //texturing calculations
//       // int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
//       int texNum;
//       if (side == 0) {  // Est/Ouest
//         if (stepX > 0) {
//           texNum = 0; // Texture for East
//         } else {
//           texNum = 1; // Texture for West
//         }
//       } else {  // Nord/Sud
//         if (stepY > 0) {
//           texNum = 2; // Texture for South
//         } else {
//           texNum = 3; // Texture for North
//         }
//       }
//       //calculate value of wallX
//       double wallX; //where exactly the wall was hit
//       if(side == 0) wallX = posY + perpWallDist * rayDirY;
//       else          wallX = posX + perpWallDist * rayDirX;
//       wallX -= floor((wallX));

//       //x coordinate on the texture
//       int texX = (int)(wallX * (double) texWidth);
//       if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
//       if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

//       // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
//       // How much to increase the texture coordinate per screen pixel
//       double step = 1.0 * texHeight / lineHeight;
//       // Starting texture coordinate
//       double texPos = (drawStart - pitch - WINDOW_HEIGHT / 2 + lineHeight / 2) * step;
//       for(int y = drawStart; y < drawEnd; y++)
//       {
//         // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
//         int texY = (int)texPos & (texHeight - 1);
//         texPos += step;
//         int color = texture[texNum][texHeight * texY + texX];
//         if(side == 1) color = (color >> 1) & 8355711;
//         buffer[y][x] = color;
//       }
//     }
// 	return (buffer);
// }