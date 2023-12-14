import unreal
import os
import argparse

def convertWindowsToLinux(windowsPath):
    drive, rest = windowsPath.split(':', 1)
    drive = drive.lower()

    # Replace backslashes with forward slashes
    rest = rest.replace('\\', '/')

    # Combine the components and add "/mnt" at the beginning
    unix_path = f'/mnt/{drive}{rest}'
    return unix_path

def convert_unix_to_windows_path(unix_path):
    # Replace forward slashes with the appropriate separator for the current OS
    windows_path = unix_path.replace('/', os.sep)

    # Check if the path starts with '/mnt/' and convert it to the corresponding drive letter
    if windows_path.startswith('\mnt\\'):
        drive_letter = windows_path[5].upper()  # Assuming the drive letter is always single character
        windows_path = drive_letter + ':' + windows_path[6:]

    return windows_path

def main():
    args = parse_arguments()
    output_base_name = os.path.splitext(os.path.basename(convertWindowsToLinux(args.inputImage)))[0]
    unreal.log(convertWindowsToLinux(args.outputPath))
    output_location = convertWindowsToLinux(args.outputPath)
    output_dir_path = convert_unix_to_windows_path(os.path.join(output_location, output_base_name))

    output_mesh_path = os.path.join(output_dir_path, output_base_name+".obj")
    unreal.log(output_mesh_path)
    unreal.log(os.path.exists(output_mesh_path))
    objPath = os.path.join(output_dir_path, output_base_name+".obj")

    unreal.log(f"importing {objPath} to {args.outputDirectoryName}")

    # importAssets(os.path.join(output_dir_path, output_base_name+".obj"), args.outputDirectoryName)

def parse_arguments():
    parser = argparse.ArgumentParser(description='Uploads Output')
    parser.add_argument('--inputImage', required=True, help='Path to the input image')
    parser.add_argument('--outputPath', required=True, help='Path to the DECA results')
    parser.add_argument('--outputDirectoryName', default='FaceMesh', help='Optional output directory name (default: FaceMesh)')

    return parser.parse_args()

def importAssets(objFilePath, destination_folder_name):

    # need to change this
    # ./../../../../../Users/ryryk/Documents/UnrealProjects/SeniorProjectDemo/Plugins/FaceMeshGenerator/import.py --inputImage "C:/Users/ryryk/Desktop/ryan2.png" --outputPath "C:/Users/ryryk/Documents/UnrealProjects/SeniorProjectDemo/"


    # Create an instance of InterchangeGenericAssetsPipeline
    pipeline = unreal.InterchangeGenericAssetsPipeline()

    # Configure the pipeline settings
    pipeline.import_offset_rotation = unreal.Rotator(90, 0, 0)
    pipeline.import_offset_translation = unreal.Vector(0, 0, 0)
    pipeline.import_offset_uniform_scale = 400.0
    pipeline.use_source_name_for_asset = True

    # Replace 'obj_file_path' with the actual path to your OBJ file

    # Specify the destination folder path
    destination_folder_path = os.path.join("/Game/", destination_folder_name) # Change this to your desired destination path

    source_data = unreal.InterchangeManager.create_source_data(objFilePath)
    import_asset_parameters = unreal.ImportAssetParameters()
    # import_asset_parameters.is_automated = True

    eas = unreal.get_editor_subsystem(unreal.EditorAssetSubsystem)
    import_asset_parameters.override_pipelines.append(pipeline)

    ic_mng = unreal.InterchangeManager.get_interchange_manager_scripted()
    # can try aasync
    ic_mng.import_scene(destination_folder_path, source_data, import_asset_parameters)

main()
# args = parse_arguments()
#
# unreal.log("hello")
