nnoremap q :call WordQuote()<CR>

function WordQuote ()
	:execute ":normal Bi\""
	:execute ":normal Ea\""
endfunction

