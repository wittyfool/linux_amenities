nnoremap q :call WordQuote()<CR>

function WordQuote ()
"	:execute ":normal Bi\""
"
"
	:execute ":normal WB"
	:let c = matchstr(getline('.'), '.', col('.')-1)
	:if c !~ "\""
	:  execute ":normal i\""
	:endif
	:execute ":normal E"
	:let c = matchstr(getline('.'), '.', col('.')-1)
	:if c !~ "\""
	:  execute ":normal a\""
	:endif
endfunction

