#!/bin/sh
ed a_text_file <<!FunkyStuff!
3      # Go to line 3
d      # Delete line 3
.,\$s/is/was/  # Replace 'is' with 'was' from the current line to the last line
w      # Write (save) the changes to the file
q      # Quit the editor
!FunkyStuff!
exit 0

