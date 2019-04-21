import cv2
import numpy as np

#Read the images
source = cv2.imread("../assets/src.jpeg")
destination = cv2.imread("../assets/dest.jpeg")

#initialize result image
result = np.copy(destination)

#convert to LAB color space
sourceLab = cv2.cvtColor(source, cv2.COLOR_BGR2Lab)
destinationLab = cv2.cvtColor(destination, cv2.COLOR_BGR2LAB)
resultLab = cv2.cvtColor(result, cv2.COLOR_BGR2Lab)

#convert to float32
sourceLab = np.float32(sourceLab)
destinationLab = np.float32(destinationLab)
resultLab = np.float32(resultLab)

#split into channels
sourceL, sourceA, sourceB = cv2.split(sourceLab)
destinationL, destinationA, destinationB = cv2.split(destinationLab)
resultL, resultA, resultB = cv2.split(resultLab)

#subtract the mean of the destination. This in a way removes the base color of the destination image.
resultL = destinationL - destinationL.mean()
resultA = destinationA - destinationA.mean()
resultB = destinationB - destinationB.mean()

#scale the standard deviation of the destination 
resultL = resultL * (sourceL.std()/ destinationL.std())
resultA = resultA * (sourceA.std()/ destinationA.std())
resultB = resultB * (sourceB.std()/ destinationB.std())

#add mean of the source image
resultL = resultL + sourceL.mean()
resultA = resultA + sourceA.mean()
resultB = resultB + sourceB.mean()

#make sure all image values are in the range 0 and 255
resultL = np.clip(resultL, 0, 255)
resultA = np.clip(resultA, 0, 255)
resultB = np.clip(resultB, 0, 255)

#merge back the channels
resultLab = cv2.merge([resultL, resultA, resultB])

#convert back from float32
resultLab = np.uint8(resultLab)

#convert back to RGB color space
result =  cv2.cvtColor(resultLab, cv2.COLOR_LAB2BGR)

#create windows to display images
cv2.namedWindow("source", cv2.WINDOW_NORMAL)
cv2.namedWindow("destination", cv2.WINDOW_NORMAL)
cv2.namedWindow("result", cv2.WINDOW_NORMAL)

#display images
cv2.imshow("source", source)
cv2.imshow("destination", destination)
cv2.imshow("result", result)

#press esc to exit the program
cv2.waitKey(0)

#close all the opened windows
cv2.destroyAllWindows()