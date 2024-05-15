import os
import time

import matplotlib.pyplot as plt
from azure.cognitiveservices.vision.computervision import ComputerVisionClient
from azure.cognitiveservices.vision.computervision.models import OperationStatusCodes
from azure.cognitiveservices.vision.computervision.models import VisualFeatureTypes
from msrest.authentication import CognitiveServicesCredentials

'''
Authenticate
Authenticates your credentials and creates a client.
'''
subscription_key = "ad2b1d8267384aceb2f04586adf2723e"
endpoint = "https://cosminandrei-ai.cognitiveservices.azure.com//"
computervision_client = ComputerVisionClient(endpoint, CognitiveServicesCredentials(subscription_key))
'''
END - Authenticate
'''

# Sa se foloseasca un algoritm de clasificare a imaginilor (etapa de inferenta/testare) si sa se stabileasca
# performanta acestui algoritm de clasificare binara (imagini cu biciclete vs. imagini fara biciclete).

def images_reader():
    folder_path = "bikes"
    image_files = []
    for filename in os.listdir(folder_path):
        if filename.endswith(".jpg"):
            image_path = os.path.join(folder_path, filename)
            image_files.append(image_path)

    return image_files


def clasified_image(image_files):
    computedLabels = []
    for image in image_files:
        img = open(image, "rb")
        result = computervision_client.analyze_image_in_stream(img, visual_features=[VisualFeatureTypes.tags,
                                                                                     VisualFeatureTypes.objects])

        computed_label = 'non-bike'

        for ob in result.objects:
            if (ob.object_property == "bike" or ob.object_property == "cycle" or ob.object_property == "cycling" or
                    ob.object_property == "bicycle" or ob.object_property == "bikes"):
                computed_label = 'bike'

        computedLabels.append(computed_label)

    realLabels = ['bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'non-bike',
                  'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike',
                  'non-bike']
    labelNames = ['bike', 'non-bike']

    from sklearn.metrics import confusion_matrix, accuracy_score, precision_score, recall_score

    cm = confusion_matrix(realLabels, computedLabels, labels=labelNames)
    acc = accuracy_score(realLabels, computedLabels)
    precision = precision_score(realLabels, computedLabels, average=None, labels=labelNames)
    recall = recall_score(realLabels, computedLabels, average=None, labels=labelNames)
    return acc, precision, recall


def plotLocalization(image_files):
    predictedBoxes = []
    for image in image_files:
        predicted_bike = []
        ok = 0
        img = open(image, "rb")
        result = computervision_client.analyze_image_in_stream(img, visual_features=[VisualFeatureTypes.objects])
        for ob in result.objects:
            if (ob.object_property == "bike" or ob.object_property == "cycle" or ob.object_property == "cycling" or
                    ob.object_property == "bicycle" or ob.object_property == "bikes"):
                ok = 1
                predicted_bike = [ob.rectangle.x, ob.rectangle.y, ob.rectangle.x + ob.rectangle.w,
                                  ob.rectangle.y + ob.rectangle.h]
                predictedBoxes.append(predicted_bike)

        # 1a
        if ok == 1:
            im = plt.imread(image)
            fig = plt.imshow(im)
            fig.axes.add_patch(plt.Rectangle(xy=(predicted_bike[0], predicted_bike[1]),
                                             width=predicted_bike[2] - predicted_bike[0],
                                             height=predicted_bike[3] - predicted_bike[1], fill=False, color="green",
                                             linewidth=2))

            # plt.show()

    return predictedBoxes


def plotManual(image_files):
    boxes = [
        [5, 32, 400, 374],
        [17, 88, 362, 234],
        [157, 145, 186, 261],
        [3, 1, 412, 414],
        [69, 45, 288, 301],
        [160, 145, 186, 261],
        [61, 204, 237, 212],
        [54, 2, 333, 353],
        [4, 8, 378, 376],
        [142, 125, 234, 284]
    ]

    for i, image in enumerate(image_files[:10], start=0):
        im = plt.imread(image)
        fig = plt.imshow(im)
        fig.axes.add_patch(plt.Rectangle(xy=(boxes[i][0], boxes[i][1]),
                                         width=boxes[i][2],
                                         height=boxes[i][3], fill=False, color="green",
                                         linewidth=2))

        plt.show()
        i = i + 1


def quality(realBoxes, predictedBoxes):
    for i in range(len(realBoxes)):
        err = 0
        for v in zip(predictedBoxes[i], realBoxes[i]):
            err = err + (v[0] - v[1]) ** 2
        err /= 4
        print("picture nr ", i)
        print("detection error ", err)


def main():
    image_files = images_reader()
    acc, prec, recall = clasified_image(image_files)
    # print('Exercitiul 1: Classification')
    print('acc: ', acc, ' precision: ', prec, ' recall: ', recall)

    predictedBoxes = plotLocalization(image_files)
    # plotManual(image_files)
    realBoxes = [
        [5, 32, 400, 374],
        [17, 88, 362, 234],
        [157, 145, 186, 261],
        [3, 1, 412, 414],
        [69, 45, 288, 301],
        [160, 145, 186, 261],
        [61, 204, 237, 212],
        [4, 8, 378, 376],
        [142, 125, 234, 284]
    ]
    # quality(realBoxes, predictedBoxes)


main()
