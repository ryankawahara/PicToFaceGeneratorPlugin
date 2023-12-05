def getUnrealPythonExecutable():
    correct_dir = (os.path.dirname(os.path.dirname(sys.executable)))
    path_parts = correct_dir.split(os.path.sep)
    path_parts.append('ThirdParty')
    path_parts.append('Python3')
    path_parts.append('Win64')
    path_parts.append('python.exe')
    return os.path.sep.join(path_parts)

def convertWindowsToLinux(windowsPath):
    drive, rest = windowsPath.split(':', 1)
    drive = drive.lower()

    # Replace backslashes with forward slashes
    rest = rest.replace('\\', '/')

    # Combine the components and add "/mnt" at the beginning
    unix_path = f'/mnt/{drive}{rest}'
    return unix_path
