# String-replacer

This project replaces the placeholders ${namespace:key} in the parsed string with the value obtained from the variables file
"<namespace>.properties" that matches the key of the placeholder.

Reads the commands from STDIN and writes results to STDOUT. Reporting of error conditions is done via STDERR. 

INPUT:
<keyword> [parameters] 

Keyword: language/replace/quit

The command for changing language is: language [country_code] 
Note: The folder(en/fr) which contains the variable files should be in the same path as source files.

Replacements are submitted to the program using the replace command: replace "[String to process]" [preserveUnmatched=false] 

Exit the program : quit
