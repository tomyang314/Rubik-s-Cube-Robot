import cv2 as cv
import numpy as np


class Frame:
    def __init__(self, size):
        self.size = size
        self.dict = {0: [np.array([[-1, 0], [0, -1]]),
                         np.array([[-1, 0], [-1, 0]]),
                         np.array([[0, -1], [-1, 0]])],
                     1: [np.array([[0, 1], [-1, 0]]),
                         np.array([[1, 0], [-1, 0]]),
                         np.array([[1, 0], [0, -1]])],
                     2: [np.array([[1, 0], [0, 1]]),
                         np.array([[1, 0], [1, 0]]),
                         np.array([[0, 1], [1, 0]])],
                     3: [np.array([[0, -1], [1, 0]]),
                         np.array([[-1, 0], [1, 0]]),
                         np.array([[-1, 0], [0, 1]])]
                     }

    def draw_fr(self, img):
        length = self.size
        l1 = int(length/2)
        l2 = int(length/3)
        l3 = l1 - l2

        center_x, center_y = int(img.shape[1] / 2), int(img.shape[0] / 2)
        blk = np.zeros(img.shape, np.uint8)
        for i in range(4):
            pt1 = (center_x+int(np.dot([l1, l3], self.dict[i][0][0])),
                   center_y+int(np.dot([l1, l3], self.dict[i][0][1])))
            pt2 = (center_x+int(np.dot([l1, l3], self.dict[i][1][0])),
                   center_y+int(np.dot([l1, l3], self.dict[i][1][1])))
            pt3 = (center_x+int(np.dot([l1, l3], self.dict[i][2][0])),
                   center_y+int(np.dot([l1, l3], self.dict[i][2][1])))
            cv.line(blk, pt1, pt2, (255, 255, 0), 5)
            cv.line(blk, pt2, pt3, (255, 255, 0), 5)

        img = cv.addWeighted(img, 1.0, blk, 0.4, 1)
        # cv.circle(img, (center_x, center_y), 1, (0, 0, 255), 5)
        return img


class Box:
    def __init__(self, size):
        self.size = size

    def draw_box(self, img):
        length = self.size
        blk = np.zeros(img.shape, np.uint8)
        center_x, center_y = int(img.shape[1] / 2), int(img.shape[0] / 2)
        x, y = center_x-int(length/2), center_y-int(length/2)
        for i in range(-1, 2):
            for j in range(-1, 2):
                p1, p2 = x+int(j*length*2), y+int(i*length*2)

                cv.rectangle(img, (p1, p2), (p1+length, p2+length), (240, 32, 160), 1)
        # cv.rectangle(img, (x, y), (x+length, y+length), (0, 255, 0), 1)
        img = cv.addWeighted(img, 1.0, blk, 0.4, 1)
        return img


if __name__ == '__main__':
    cap = cv.VideoCapture(0)
    # fr = Frame(200)
    box = Box(30)

    while True:
        _, frame = cap.read()
        frame = cv.flip(frame, 1)
        # frame = fr.draw_fr(frame)
        frame = box.draw_box(frame)
        cv.imshow("ss", frame)

        if cv.waitKey(5) & 0xff == 27:
            break

    cap.release()
    cv.destroyAllWindows()






