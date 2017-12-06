#!/usr/bin/env python
import sys

from PIL import Image
 
name = 'test3'

im = Image.open('resources/'+name+'.jpg') #relative path to file
 
#load the pixel info
pix = im.load()
 
#get a tuple of the x and y dimensions of the image
width, height = im.size
 
#open a file to write the pixel data
with open('tests/'+name+'.csv', 'w+') as f:
  #stores width,height
  f.write('{0},{1}\n'.format(width,height))

  #read the details of each pixel and write them to the file
  for y in range(height):
    for x in range(width):
        #print(str(pix[x,y][0])+'-'+str(pix[x,y][1])+'-'+str(pix[x,y][2])+'-')
      r = str(pix[x,y][0])#.zfill(3)
      g = str(pix[x,y][1])#.zfill(3)
      b = str(pix[x,y][2])#.zfill(3)
      
      #r = hex(pix[x,y][0]).split('x')[-1].zfill(3)
      #g = hex(pix[x,y][1]).split('x')[-1].zfill(3)
      #b = hex(pix[x,y][2]).split('x')[-1].zfill(3)
      #f.write('#{0}{1}{2}, '.format(r,g,b))
      f.write('{0},{1},{2},'.format(r,g,b))
    #f.write('\n')
  f.write('\n')

print(name+'.csv of size '+str(width)+'x'+str(height)+' has been created and put into TESTS directory!\n')

if(len(sys.argv) > 1):
    print(sys.argv[1:])
