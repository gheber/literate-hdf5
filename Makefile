hdf = *.h5 *.hdf5
media = *.gif *.html *.pdf *.tex
objects = *.o

.PHONY : clean
clean :
	-rm $(hdf) $(media) $(objects)
