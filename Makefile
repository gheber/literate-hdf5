hdf = *.h5
media = *.html *.pdf *.tex
objects = *.o

.PHONY : clean
clean :
	-rm $(hdf) $(media) $(objects)
