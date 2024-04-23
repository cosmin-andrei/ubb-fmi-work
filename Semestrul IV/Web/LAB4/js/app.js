function pb1(item, select, index) {
  let target, source;
  if (select === 'left') {
    target = 'right';
    source = 'left';
  } else if(select === 'right') {
    target = 'left';
    source = 'right';
  }

  let option = document.createElement('option');
  option.text = item;
  target.add(option);

}
