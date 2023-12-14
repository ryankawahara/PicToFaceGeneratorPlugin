import cv2
import argparse
import tempfile
import os

import numpy as np
import unreal
import pathlib

SCRIPT_PATH = os.path.dirname(__file__)

def parse_arguments():
    parser = argparse.ArgumentParser(description='Crop Input Image to square face')
    parser.add_argument('--inputImage', required=True, help='Path to the input image')
    parser.add_argument('--outputFolderName', required=True, help='Path to the input image')


    return parser.parse_args()


def main():
    args = parse_arguments()

    current_directory = os.path.dirname(SCRIPT_PATH)

    contentPath = unreal.Paths.project_content_dir()

    pluginsPath = unreal.Paths.make_standard_filename(unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_plugins_dir()))
    message = f"Content is at {contentPath}"

    image = cv2.imread(args.inputImage)

    # Get the path to the temporary directory
    temp_dir = tempfile.gettempdir()

    file_path = pathlib.Path(args.inputImage)

    # Get the filename (stem)
    name = file_path.stem


    # Get the file extension
    extension = file_path.suffix

    output_path = os.path.join(temp_dir, f'{name}_crop{extension}')

    unreal.log(output_path)

    # Save the black and white image to the temporary directory
    face = detectFace(image)

    cv2.imwrite(output_path, face)

    importAssets(output_path, args.outputFolderName+f"/{name}_crop", name)

def detectFace(image, padding = 50):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_alt2.xml')
    #
    faces = face_cascade.detectMultiScale(gray, 1.1, 4)
    #
    face = np.zeros(image.shape)
    for (x, y, w, h) in faces:
        face = image[y - padding:y + h + padding, x - padding:x + w + padding]

    return face

def importAssets(fileNames, destinationName , fileName):
    if isinstance(fileNames, str):
        fileNames = [fileNames]

    assetTools = unreal.AssetToolsHelpers.get_asset_tools()

    assetImportData = unreal.AutomatedAssetImportData()

    assetImportData.destination_path = os.path.join("/Game/", destinationName, "Source")

    assetImportData.filenames = fileNames
    assetTools.import_assets_automated(assetImportData)



main()