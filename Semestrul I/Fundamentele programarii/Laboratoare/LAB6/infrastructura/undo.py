def add_to_undo(l,undo_l):
    '''
    Adds the current list to the undo list
    :param l: lista
    :param undo_list: lista
    :return: -
    '''
    undo_l.append(l[:])

def undo(l,undo_l):
    '''
    Undo ultima operatie schimband lista curenta cu cea de backup
    :param l: lista
    :param undo_l: lista
    :return: -
    '''

    l.clear()
    for i in undo_l[-1]:
        l.append(i)
    undo_l.pop()