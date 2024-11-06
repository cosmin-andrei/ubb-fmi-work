$(document).ready(function() {
    const $treeView = $('#tree-view');
    const $fileContent = $('#file-content');

    function loadDirectory(path, $element) {
        $.ajax({
            url: 'server.php',
            method: 'GET',
            data: { path: path },
            dataType: 'json',
            success: function(data) {
                const $ul = createTree(data);
                if ($element) {
                    $element.append($ul);
                } else {
                    $treeView.append($ul);
                }
            },
            error: function(xhr, status, error) {
                console.error('Error:', error);
            }
        });
    }

    function createTree(data) {
        const $ul = $('<ul>');

        $.each(data, function(index, item) {
            const $li = $('<li>');

            if (item.type === 'directory') {
                $li.addClass('folder').text(item.name).click(function() {
                    if ($li.children('ul').length === 0) {
                        loadDirectory(item.path, $li);
                    }
                    $li.toggleClass('open');
                });
            } else {
                $li.addClass('file').text(item.name).click(function() {
                    loadFile(item.path);
                });
            }

            $ul.append($li);
        });

        return $ul;
    }

    function loadFile(path) {
        $.ajax({
            url: 'server.php',
            method: 'GET',
            data: { file: path },
            success: function(data) {
                $fileContent.text(data);
            },
            error: function(xhr, status, error) {
                console.error('Error:', error);
            }
        });
    }

    loadDirectory('D://Facultate/ubb-fmi-work/Semestrul IV/Web/LAB6/problema 5');
});
