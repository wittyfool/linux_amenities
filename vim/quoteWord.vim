nnoremap q :call WordQuote("\'")<CR>
nnoremap Q :call WordQuote("\"")<CR>

function WordQuote (x)
	:execute ":normal WB"
	:let c = matchstr(getline('.'), '.', col('.')-1)
	:if c !~ a:x
	:  execute ":normal i".a:x
	:endif
	:execute ":normal E"
	:let c = matchstr(getline('.'), '.', col('.')-1)
	:if c !~ a:x
	:  execute ":normal a".a:x
	:endif
endfunction

