$(document).ready(function() {
    $('#first, #second, #third').on('dblclick', function() {
        let id = $(this).attr('id');
        switch(id) {
            case 'first':
                pb1($('#first'), $('#second'));
                break;
            case 'second':
                pb1($('#second'), $('#third'));
                break;
            case 'third':
                pb1($('#third'), $('#second'));
                break;
        }
    });

    function pb1(source, target) {
        let selectedIndex = source.prop('selectedIndex');
        if (selectedIndex >= 0) {
            let selectedItem = source.find('option').eq(selectedIndex);
            let option = $('<option>', {value: selectedItem.val(), text: selectedItem.text()});
            target.append(option);
            source.find('option').eq(selectedIndex).remove();
        }
    }
});