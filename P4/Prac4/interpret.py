# -*- encoding: utf-8 -*-

class Interpret(object):
    def __init__(self):
        """

        Simula un interpret per poder realtizar accions a traves del terminal
        
        """
        self._d={}
        self._prompt=''
    def get_prompt(self):
        return self._prompt
    def get_ordre(self):
        return self._d
    def set_prompt(self,p):
        """

        Fixa l'string p com el prompt de l'interpret
        
        >>> i= Interpret()
        >>> i.set_prompt('#')
        >>> i.get_prompt()
        '#'

        """
        self._prompt=p
    def afegeix_ordre(self,nomc,ordre):
        """

        Afegeix a l'interpret una ordre de nom nomc associada a la funcio ordre.
        
        >>> i= Interpret()
        >>> i.afegeix_ordre('producte', 'funcio')
        >>> i.afegeix_ordre('producte','cosa')
        Ja existeix aquesta ordre
        >>> i.afegeix_ordre('recepta', 'prova')
        >>> i.get_ordre()
        {'producte': 'funcio', 'recepta': 'prova'}
        
        """
        if nomc in self._d.keys():
            print "Ja existeix aquesta ordre"
        else:
            self._d[nomc]=ordre
    def run(self):
        """

        Arrenca l'execucio de l'interpret

        """
        teclat=raw_input(self._prompt+' ')
        llista=teclat.split()
        while llista[0]!='surt':     
            llista=teclat.split()
            nomc=llista[0]
            if nomc in self._d.keys():
                self._d[nomc]()
            else:
                print "No existeix aquesta ordre"
            teclat=raw_input(self._prompt+' ')
            llista=teclat.split()
    def ajuda(self):
        """
        """
        for element in self._d.keys():
            print element

