#!/usr/bin/env python
import sys

from PIL import Image
 
im = Image.open('resources/test1.jpg') #relative path to file
 
#load the pixel info
pix = im.load()
 
#get a tuple of the x and y dimensions of the image
width, height = im.size
 
#open a file to write the pixel data
with open('tests/test1.csv', 'w+') as f:
  #stores width,height
  f.write('{0},{1}\n'.format(width,height))
 
  #read the details of each pixel and write them to the file
  for y in range(height):
    for x in range(width):
      r = hex(pix[x,y][0]).split('x')[-1].zfill(2)
      g = hex(pix[x,y][1]).split('x')[-1].zfill(2)
      b = hex(pix[x,y][2]).split('x')[-1].zfill(2)
      f.write('#{0}{1}{2}, '.format(r,g,b))
    f.write('\n')
  f.write('\n')

if(len(sys.argv) > 1):
    print(sys.argv[1:])
