import cv2
import os
import os.path
from sys import argv

def file_extension(path):
    tmp_str = os.path.splitext(path)[1]
    if tmp_str[0:1] == '.':
        result = tmp_str[1:]
    else:
        result = tmp_str
    return result

def img_info(img):
    size = img.shape
    height = size[0]
    width = size[1]
    channels = 1
    if len(size) == 3:
        channels = size[2]
    return width, height, channels

class MediaInfo(object):
    def __init__(self):
        self.media_handle_functions = {
            'bmp': self.handle_image,
            'png': self.handle_image,
            'jpg': self.handle_image,
            'mp4': self.handle_video,
            #'.avi': self.handle_avi,
        }


    def handle_image(self, media_path):
        img = cv2.imread(media_path, cv2.IMREAD_UNCHANGED)
        ext_name = file_extension(media_path)
        w, h, c = img_info(img)
        return "{0} {1} {2} {3} {4}".format(ext_name, w, h, c, 1)

    def handle_video(self, media_path):
        valid_media = True
        frame_cnt = 0
        ext_name = file_extension(media_path)
        cap = cv2.VideoCapture(media_path)
        width = height = channels = 0
        while 1:
            ret, img = cap.read()
            if not ret:
                break
            if frame_cnt == 0:
                width, height, channels = img_info(img)
            else:
                w, h, c = img_info(img)
                valid_media = ((w == width) and (h == height) and (c == channels))

            if not valid_media:
                break
            frame_cnt = frame_cnt + 1 
        if valid_media:
            return "{0} {1} {2} {3} {4}".format(ext_name, width, height, channels, frame_cnt)
        else:
            return "none {0}".format(media_path)


    def check_media(self, media_path):
        if not os.path.isfile(media_path):
            print("none {0}".format(media_path))
            exit(-1)
        ext_name = file_extension(media_path)
        info_str = self.media_handle_functions[ext_name](media_path)
        print(info_str)

if __name__ == '__main__':
    script, media_path = argv
    media_info = MediaInfo()
    media_info.check_media(media_path)
