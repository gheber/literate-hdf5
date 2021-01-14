
hdf = *.h5 *.hdf5
media = *.gif *.html *.pdf *.tex
objects = *.o
org_files = $(wildcard *.org)

tangle:
	for org in $(org_files); do \
		emacs --batch --eval \
			"(progn (require 'ob-tangle) (org-babel-tangle-file \"$$org\"))" ; \
	done

.PHONY : clean
clean :
	-rm $(hdf) $(media) $(objects)
