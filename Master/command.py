import cv2 as cv
from tools import Box
import color_histogram_feature_extraction
import knn_classifier
import kociemba


color_dict = {"red": 'R', "orange": 'L', "yellow": 'U', "green": 'B', "blue": 'F', "white": 'D'}


def color_get(img, size):
    color_list = []
    length = size
    center_x, center_y = int(img.shape[1] / 2), int(img.shape[0] / 2)
    x, y = center_x - int(length / 2), center_y - int(length / 2)
    for i in range(-1, 2):
        for j in range(-1, 2):
            if i == 0 and j == 0:
                color_list.append('0')
                continue
            p1, p2 = x + int(j * length * 2), y + int(i * length * 2)
            box = img[p2:p2 + length, p1:p1 + length]
            color_histogram_feature_extraction.color_histogram_of_test_image(box)
            color = knn_classifier.main('training.data', 'test.data')
            color_list.append(color_dict[color])

    return color_list


def recovery_code(code_dict):
    code_list = ['U', 'R', 'F', 'D', 'L', 'B']
    code = []
    for _, number in enumerate(code_list):
        code += code_dict[number]
    print('-'*100)
    code_string = ''.join(code)
    cube_image(code_string)
    print('-'*100)
    ko_data = kociemba.solve(code_string)
    code1 = ko_data.split(' ')
    for index, val in enumerate(code1):
        if len(val) == 1:
            code1[index] = val + ' '

    return ''.join(code1)


def cube_image(string):
    for i in range(3):
        print("       " + ' '.join(string[i * 3: (i + 1) * 3]))

    for i in range(3):
        print(' '.join(string[36 + i * 3: 39 + i * 3]) + '  ' + ' '.join(string[18 + i * 3: 21 + i * 3])
              + '  ' + ' '.join(string[9 + i * 3: 12 + i * 3]) + '  ' + ' '.join(string[45 + i * 3: 48 + i * 3]))

    for i in range(3):
        print("       " + ' '.join(string[27 + i * 3: 30 + i * 3]))


def get_command():
    cap = cv.VideoCapture(1)
    b = Box(30)
    dictionary = {}
    listing = ['F', 'R', 'B', 'L', 'U', 'D']

    counts = 0
    while True:
        # Capture frame-by-frame
        ret, frame = cap.read()
        frame = b.draw_box(frame)
        frame1 = frame.copy()
        cv.imshow('color classifier', frame)

        enter = cv.waitKey(1) & 0xff
        if enter == 27:
            break
        elif enter == 32:
            face_color = color_get(frame1, 30)
            face_color[4] = listing[counts]
            print(face_color)
            dictionary[listing[counts]] = face_color
            counts += 1
            if counts == 6:
                try:
                    solve_command = recovery_code(dictionary)
                    # print(solve_command)
                    return solve_command
                except ValueError:
                    print("Solve Error!")
                    print("Detection Again...")
                    print('-'*100)
                    counts = 0
                    continue

    # When everything done, release the capture
    cap.release()
    cv.destroyAllWindows()


if __name__ == '__main__':
    # cap = cv2.VideoCapture("http://admin@admin/192.168.43.1:8081")
    m_code = get_command()
    if m_code:
        print(' '.join(m_code))
