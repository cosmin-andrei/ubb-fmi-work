<?php
if (isset($_GET['path'])) {
    $path = $_GET['path'];
    $result = [];

    if (is_dir($path)) {
        $dir = new DirectoryIterator($path);
        foreach ($dir as $fileinfo) {
            if (!$fileinfo->isDot()) {
                $result[] = [
                    'name' => $fileinfo->getFilename(),
                    'type' => $fileinfo->isDir() ? 'directory' : 'file',
                    'path' => $fileinfo->getPathname()
                ];
            }
        }
    }
    header('Content-Type: application/json');
    echo json_encode($result);
} elseif (isset($_GET['file'])) {
    $file = $_GET['file'];
    if (is_file($file)) {
        header('Content-Type: text/plain');
        readfile($file);
    }
}
