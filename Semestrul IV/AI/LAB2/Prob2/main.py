"""Se dau mai multe imagini (salvate in folder-ul "data/images"). Se cere:
- sa se vizualizeze una din imagini
- daca imaginile nu aceeasi dimensiune, sa se redimensioneze toate la 128 x 128 pixeli si sa se vizualizeze imaginile
intr-un cadru tabelar.
- sa se transforme imaginile in format gray-levels si sa se vizualizeze
- sa se blureze o imagine si sa se afiseze in format "before-after"
- sa se identifice muchiile ontr-o imagine si sa se afiseze in format "before-after\""""

import os
import random
import cv2
import numpy as np

from matplotlib import image as mpimg, pyplot as plt
from PIL import Image, ImageFilter

'''
vizualizare(name) - vizualizeaza o imagine
name - calea catre imagine
'''


def vizualizare(name):
    img = mpimg.imread(name)
    plt.imshow(img)
    plt.show()


'''
resize_img(file, size) - redimensioneaza o imagine
file - calea catre imagine
size - dimensiunea la care se redimensioneaza imaginea
'''


def resize_img(file, size):
    img = Image.open(file)
    img_modified = img.resize(size)
    return img_modified


'''
vizualizare_tabelar(files) - vizualizeaza imaginile intr-un cadru tabelar (toate 128x128 pixeli)
files - lista de imagini
'''


def vizualizare_tabelar(files):
    img_resized = [Image.open(os.path.join('data', file)).resize((128, 128)) for file in files]

    for i, img in enumerate(img_resized):
        plt.subplot(len(img_resized) // 4 + 1, 4, i + 1)  # 4 imagini pe linie si cate linii sunt necesare
        plt.imshow(img)

    plt.show()


'''
to_gray(files) - transforma imaginile in format gray-levels si le vizualizeaza
files - lista de imagini
'''


def to_gray(files):
    img_gray = [Image.open(os.path.join('data', file)).convert("L") for file in files]

    for i, img in enumerate(img_gray):
        plt.subplot(len(img_gray) // 4 + 1, 4, i + 1)  # 4 imagini pe linie si cate linii sunt necesare
        plt.imshow(img)

    plt.show()


'''
blur_image(file) - blureaza o imagine si o afiseaza in format "before-after"
file - calea catre imagine
'''


def blur_image(file):
    img = Image.open(file)
    img_blurred = img.filter(ImageFilter.BLUR)

    plt.subplot(1, 2, 1)
    plt.imshow(img)
    plt.title("Before")

    plt.subplot(1, 2, 2)
    plt.imshow(img_blurred)
    plt.title("After")
    plt.show()


# sa se identifice muchiile ontr-o imagine si sa se afiseze in format "before-after
def find_edges(file):
    image = Image.open(file)
    image_edges = image.filter(ImageFilter.FIND_EDGES)

    plt.subplot(1, 2, 1)
    plt.imshow(image)
    plt.title("Before")

    plt.subplot(1, 2, 2)
    plt.imshow(image_edges)
    plt.title("After")

    plt.show()


'''
main() - functia principala
'''


def main():
    files = os.listdir('data')
    file = random.choice(files)
    vizualizare(os.path.join('data', file))
    vizualizare_tabelar(files)
    to_gray(files)
    blur_image(os.path.join('data', file))
    find_edges(os.path.join('data', file))


# main()


def normalizare(files):
    for file in files:
        cale_imagine = os.path.join('data', file)
        image = Image.open(cale_imagine)
        img_array = np.array(image)
        norm_img = np.log1p(img_array)  # normalizare log scalling
        norm_img = norm_img.astype(np.uint8)  # le transform in int
        plt.axis('off')
        plt.imshow(norm_img)
        plt.show()
        

normalizare(os.listdir('data'))
