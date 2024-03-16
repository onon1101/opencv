import cv2
import matplotlib.pyplot as plt
import numpy as np

def draw_lines(img, lines, color=[255,255, 0], thickness=3):
    img = np.copy(img)
    img_channels = img.shape[2]
    img_lines = np.zeros((img.shape[0], img.shape[1], img_channels), dtype=np.uint8)
    for line in lines:
        for x1, y1, x2, y2 in line:
            cv2.line(img_lines, (x1, y1), (x2, y2), [255, 255, 0], 3)

    img_draw = cv2.addWeighted(img, 0.8, img_lines, 1.0, 0.0)
    return img_draw

def Simulate(img, lines):
    left_x, left_y, right_x, right_y = [], [], [], []

    for line in lines:
        for x1, y1, x2, y2 in line:
            slope = (y2-y1)/(x2-x1)
            if abs(slope) < 0.5:
                continue
            elif slope < 0:
                left_x.extend([x1, x2])
                left_y.extend([y1, y2])
            elif slope > 0:
                right_x.extend([x1, x2])
                right_y.extend([y1, y2])

    min_y, max_y = int(img.shape[0] * (3/5)), int(img.shape[0])

    # left 擬和
    poly_left = np.poly1d(np.polyfit(left_y, left_x, deg= 1))
    left_x_start, left_x_end = int(poly_left(max_y)), int(poly_left(min_y))

    # right 擬和
    poly_right = np.poly1d(np.polyfit(right_y, right_x, deg=1))
    right_x_start, right_x_end = int(poly_right(max_y)), int(poly_right(min_y))

    _img_line = draw_lines(img, [[
        [left_x_start, max_y, left_x_end, min_y],
         [right_x_start, max_y, right_x_end, min_y]
    ]], thickness=5)
    return _img_line

# 引入圖片
img_source = cv2.imread(
    'assets/3.jpg'
)

# 前處理
img_hsv = cv2.cvtColor(img_source, cv2.COLOR_RGB2HSV)
img_gray = cv2.cvtColor(img_source, cv2.COLOR_BGR2GRAY)

lower_yellow = np.array([20, 100, 100], dtype='uint8')
upper_yellow = np.array([30, 255, 255], dtype='uint8')
mask_yellow = cv2.inRange(img_hsv, lower_yellow, upper_yellow)

mask_white = cv2.inRange(img_gray, 200, 255)

mask_combination = cv2.bitwise_or(mask_yellow, mask_white)
img_yellWhite = cv2.bitwise_and(img_gray, mask_combination)

cv2.imshow("hsv", img_yellWhite)
cv2.waitKey(-1)

img_canny = cv2.Canny(img_gray, 100, 100) # low, high = not edge, edge, midden 相連為edge 不相連為not edge

# ROI
height = img_canny.shape[0]
width = img_canny.shape[1]
ROI_vertices = [(0, height), (width/2, height/2), (width, height)]

mask = np.zeros_like(img_canny)
match_mask_color = 255
cv2.fillPoly(mask, np.array([ROI_vertices], np.int32), 255)
img_ROI = cv2.bitwise_and(img_canny, mask)

# 霍夫
lines = cv2.HoughLinesP(img_ROI, 6, np.pi/180, 160, np.array([]), 40, 25)
# img_line = draw_lines(img_source, lines)

# 擬和
img_line = Simulate(img_source, lines)

cv2.imshow("mash", img_line)
# cv2.imshow("test", img)

cv2.waitKey(0)