#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>



typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgb;

int main(int argc, char **argv) {
    long dim;                              // The image's dimensions ...
    long iter;
    float div;
    char norm;
    sscanf(argv[1], "%ld", &dim);          // ... specified as a command-line arg
    sscanf(argv[2], "%ld", &iter);
    sscanf(argv[3], "%f", &div);
    sscanf(argv[4], "%c", &norm);
    long point[3][2] = {{dim/2, 0}, {dim,dim}, {0,dim}};

    rgb img[dim][dim];                    // Represents a pixel array
    memset(img, 0, dim*dim*sizeof(rgb));  // Clear all pixels with black (zeros)
    
    div = 1.1 + (.01*div);
    long x1 = 0;
    long y1 = 0;
    long x2 = 0;
    long y2 = 0;
    long rnd = 0;
    time_t t;
    srand((unsigned) time(&t));
    for (long i=0; i<iter; i++) {
        //get random number (0,1,2)
        rnd = rand() % 3;

        //choose random vertex

        y2 = point[rnd][0];
        x2 = point[rnd][1];

        //find halfway point between current point and new random vertex and set to current point
        if(norm == 's') {
            x1 = labs(((x2 + x1) / div));
            y1 = labs(((y2 + y1) / div));
        }
        else {
            x1 = labs(((x2 - x1) / div));
            y1 = labs(((y2 - y1) / div));
        }

        //set pixel in image
        img[x1][y1].red = 255;
    }
    // Write out the entire image (1 == standard output)
    write(1, img, dim*dim*sizeof(rgb));
    return 0;
}


//  ./serp 512 100000 2 n | convert -depth 8 -size 512x512 rgb:- ./example.png

//Consider three points in an image: The middle of the top row, the bottom-left corner, and the bottom-right corner.
// These points could form the three vertices of a triangle.
//Choose one of these points as the current position.
//Repeatedly:
//  1. Choose one of the three points at random.
//  2. Set a new current position halfway between the current position and the randomly chosen point.
//  3. Draw a colored pixel at the current position.
// bash script to run for animation
//x=100000
//d=2
//DIM=1600
//while (($d <= 100)); do
//./serp $DIM $x $d 'y' | convert -depth 8 -size ${DIM}x${DIM} -gravity northwest -annotate 0 "$x iterations" rgb:- ./sierp$(printf "%06d" $x).png
//        let d=d+1
//let x=x+1
//done
//        convert -delay 20 -loop 0 sierp*.png ~/sierp-anims.gif
//        rm sierp*.png
