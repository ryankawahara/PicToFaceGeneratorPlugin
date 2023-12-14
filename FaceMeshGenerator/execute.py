# Import the os module to work with file paths

import unreal
import sys
import os
import subprocess
import argparse
import tempfile
import shutil


def getUnrealPythonExecutable():
    correct_dir = (os.path.dirname(os.path.dirname(sys.executable)))
    path_parts = correct_dir.split(os.path.sep)
    path_parts.append('ThirdParty')
    path_parts.append('Python3')
    path_parts.append('Win64')
    path_parts.append('python.exe')
    return os.path.sep.join(path_parts)

def convert_unix_to_windows_path(unix_path):
    # Replace forward slashes with the appropriate separator for the current OS
    windows_path = unix_path.replace('/', os.sep)

    # Check if the path starts with '/mnt/' and convert it to the corresponding drive letter
    if windows_path.startswith('\mnt\\'):
        drive_letter = windows_path[5].upper()  # Assuming the drive letter is always single character
        windows_path = drive_letter + ':' + windows_path[6:]

    return windows_path

def convertWindowsToLinux(windowsPath):
    drive, rest = windowsPath.split(':', 1)
    drive = drive.lower()

    # Replace backslashes with forward slashes
    rest = rest.replace('\\', '/')

    # Combine the components and add "/mnt" at the beginning
    unix_path = f'/mnt/{drive}{rest}'
    return unix_path

PYTHON_BIN_PATH = getUnrealPythonExecutable()
LINUX_PYTHON_BIN_PATH = convertWindowsToLinux(PYTHON_BIN_PATH)
PLUGINS_PATH = unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_plugins_dir())
PACKAGES_PATH = os.path.join(PLUGINS_PATH, "pluginTest2", ".virtualEnv", "lib", "python3.9", "site-packages")
SCRIPT_PATH = os.path.dirname(__file__)
unreal.log(sys.path)
try:
    import numpy as np
    import cv2
except ImportError as e:
    setup()

def runBashPythonCommand(command, executable=None):
    """
    Allows you to run a command like you would in the command line
    Ex: bash -c python --version becomes runBashPythonCommand(--version)
    """
    if executable:
        execute = "bash -c " + "'" + '"' + executable + '" ' + command + "'"
    else:
        execute = "bash -c " + "'" + '"' + LINUX_PYTHON_BIN_PATH + '" ' + command + "'"

    out, err = runCommand(execute)
    return out, err

def runCommand(command, bash=False):
    if bash:
        command = f"bash -c '{command}'"

    unreal.log(f"Executing {command}")

    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    stdout, stderr = process.communicate()
    output = stdout.decode('utf-8').strip()
    errors = stderr.decode('utf-8').strip()

    unreal.log(f"Output: {output}")
    unreal.log(f"Errors: {errors}")

    return output, errors

def setup():
    commands = [
        f"\"{PYTHON_BIN_PATH}\" -m pip install numpy==1.23.1",
        f"\"{PYTHON_BIN_PATH}\" -m pip install opencv-python"
    ]

    for c in commands:
        runCommand(c)
    runBashPythonCommand("--version")

    unreal.log_warning(os.getcwd())

    current_directory = os.getcwd()

    try:
        runCommand("which gcc", bash=True)
        os.chdir(SCRIPT_PATH)
        # runBashPythonCommand("-m venv .DECAVenv --copies")
        vEnvPath = os.path.join(SCRIPT_PATH, ".copiedVenvs")
        unreal.log_warning(vEnvPath)
        #
        original_bin_path = os.path.join(vEnvPath, "bin", "python")
        # bin_path = convertWindowsToLinux(original_bin_path)
        unreal.log_warning(f"{(original_bin_path)} something")
        bin_path = convertWindowsToLinux(original_bin_path)
        unreal.log_warning(bin_path)

        libPath = convertWindowsToLinux(os.path.join(os.getcwd(), ".copiedVenvs", "bin"))

        unreal.log_warning(libPath)

        my_env = os.environ.copy()
        unreal.log(my_env)

        my_env["PATH"] = libPath + ";" + my_env["PATH"]

        unreal.log(my_env["PATH"])


        # runBashPythonCommand("--version", executable=bin_path)

        # runBashPythonCommand("-m pip install -r requirements.txt")


        # Your code here - you can perform operations in the new working directory

        # Change back to the original working directory
        os.chdir(current_directory)
        # unreal.log_warning(os.getcwd())


        # Now you are back to the original working directory
    except FileNotFoundError:
        print(f"The directory '{new_directory}' does not exist.")
    except Exception as e:
        print(f"An error occurred: {str(e)}")

    # runBashPythonCommand("-m venv .DECAVirtualEnv")

def importAssets(fileNames, destination_folder_name):
    # Create an instance of InterchangeGenericAssetsPipeline
    pipeline = unreal.InterchangeGenericAssetsPipeline()

    # Configure the pipeline settings
    pipeline.import_offset_rotation = unreal.Rotator(90, 0, 0)
    pipeline.import_offset_translation = unreal.Vector(0, 0, 0)
    pipeline.import_offset_uniform_scale = 400.0
    pipeline.use_source_name_for_asset = True

    # Replace 'obj_file_path' with the actual path to your OBJ file
    obj_file_path = fileNames

    # Specify the destination folder path
    destination_folder_path = os.path.join("/Game/", destination_folder_name) # Change this to your desired destination path

    source_data = unreal.InterchangeManager.create_source_data(fileNames)
    import_asset_parameters = unreal.ImportAssetParameters()
    # import_asset_parameters.is_automated = True

    eas = unreal.get_editor_subsystem(unreal.EditorAssetSubsystem)
    import_asset_parameters.override_pipelines.append(pipeline)

    ic_mng = unreal.InterchangeManager.get_interchange_manager_scripted()
    ic_mng.import_scene(destination_folder_path, source_data, import_asset_parameters)


def parse_arguments():
    parser = argparse.ArgumentParser(description='Your Script Description Here')
    parser.add_argument('--inputImage', required=True, help='Path to the input image')
    parser.add_argument('--outputPath', required=True, help='Path to the DECA results')
    parser.add_argument('--custom_flame_model', required=False, default=None, type=str,
                        help='path to custom model')

    return parser.parse_args()

def execute():
    args = parse_arguments()
    unreal.log_warning(args.inputImage)


def main_test():
    args = parse_arguments()
    unreal.log(args)
    # Get the current directory where the script is located
    current_directory = os.path.dirname(SCRIPT_PATH)

    # Log a message to the Unreal Engine console
    # contentPath = unreal.Paths.make_standard_filename(unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_content_dir()))
    contentPath = unreal.Paths.project_content_dir()

    pluginsPath = unreal.Paths.make_standard_filename(unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_plugins_dir()))
    message = f"Content is at {contentPath}"

    unreal.log(f"original {unreal.Paths.project_content_dir()}")


    image = cv2.imread('C:/Users/ryryk/Downloads/ironman.jpg')

    #conversion
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Get the path to the temporary directory
    temp_dir = tempfile.gettempdir()

    # Define the file path for the black and white image in the temporary directory
    output_path = os.path.join(temp_dir, 'bw_image.jpg')

    # Save the black and white image to the temporary directory
    cv2.imwrite(output_path, gray_image)

    unreal.log(output_path)


    unreal.log(f"we are here {unreal.Paths.convert_relative_path_to_full(unreal.Paths.get_relative_path_to_root())}")
    importAssets((output_path), "ProcessedFaces")

    unreal.log(f"hi {unreal.Paths.convert_relative_path_to_full(unreal.Paths.diff_dir())}")
    message = f"Hello, Unreal! {contentPath}"
    nvcc_path = shutil.which('nvcc')

    unreal.log(nvcc_path)

def main():
    # runCommand(f"\"{PYTHON_BIN_PATH}\" -m pip install ninja")

    args = parse_arguments()
    unreal.log(args)
    vEnvPath = os.path.join(SCRIPT_PATH, "DECA_Senior_Project", ".copiedVenvs")

    # Get the current directory where the script is located
    current_directory = os.path.dirname(SCRIPT_PATH)

    contentPath = unreal.Paths.project_content_dir()

    pluginsPath = unreal.Paths.make_standard_filename(
        unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_plugins_dir()))

    current_directory = os.getcwd()

    venv_bin_path = convertWindowsToLinux(os.path.join(vEnvPath, "bin", "python"))

    try:
        os.chdir(SCRIPT_PATH)

        libPath = (os.path.join(os.getcwd(), "DECA_Senior_Project", ".copiedVenvs", "bin"))
        unreal.log(os.path.exists(libPath))
        unreal.log(f"libpath = {libPath}")
        my_env = os.environ.copy()
        my_env["PATH"] = libPath + ";" + my_env["PATH"]
        unreal.log("HERE")
        unreal.log(my_env["PATH"])
        # Change back to the original working directory
        os.chdir(current_directory)
        # print(ninja.__file__)

        # Now you are back to the original working directory
    except FileNotFoundError:
        print(f"The directory does not exist.")
    except Exception as e:
        print(f"An error occurred: {str(e)}")
    unreal.log(PYTHON_BIN_PATH)
    deca_script_path = '"' + convertWindowsToLinux(os.path.join(SCRIPT_PATH, "DECA_Senior_Project", "demos", "demo_reconstruct_neutral.py")) + '"'
    exp_path = '"' + convertWindowsToLinux(os.path.join(SCRIPT_PATH, "DECA_Senior_Project", "exp")) + '"'
    input_image_path = f'"{convertWindowsToLinux(args.inputImage)}"'
    output_result_path = f'"{convertWindowsToLinux(args.outputPath)}"'
    test_script_path = '"' + convertWindowsToLinux(os.path.join(SCRIPT_PATH, "DECA_Senior_Project", "demos", "test.py")) + '"'
    # commandString = test_script_path
    commandString = f"{deca_script_path} -i {input_image_path} --saveDepth True --saveObj True --exp_path {exp_path} --savefolder {output_result_path}"

    if args.custom_flame_model:
        unreal.log(args.custom_flame_model)

        commandString += f" --custom_flame_model {convertWindowsToLinux(args.custom_flame_model)}"

    unreal.log(venv_bin_path)

    unreal.log(commandString)
    runBashPythonCommand(commandString, executable=venv_bin_path)
    output_base_name = os.path.splitext(os.path.basename(convertWindowsToLinux(args.inputImage)))[0]
    unreal.log(convertWindowsToLinux(args.outputPath))
    output_location = convertWindowsToLinux(args.outputPath)
    output_dir_path = convert_unix_to_windows_path(os.path.join(output_location, output_base_name))

    output_mesh_path = os.path.join(output_dir_path, output_base_name+".obj")
    unreal.log(output_mesh_path)
    unreal.log(os.path.exists(output_mesh_path))
    # importAssets(os.path.join(output_dir_path, output_base_name+".obj"), "FaceMesh")


main()
