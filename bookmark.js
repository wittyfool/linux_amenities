#!/usr/bin/env node

const bookmark = process.env["HOME"] + '/.config/google-chrome/Default/Bookmarks';
var fs = require('fs');

// console.log('reading bookmark ... ' + bookmark);

const jsText = fs.readFileSync( bookmark );
let objBM = JSON.parse( jsText );

const digit2 = function(d){
  if(d>=10){
    return d;
  }
  return '0' + d;
}

// Google先生の不思議な時間フォーマット
const dateStr = function(micro){
  let sec = parseInt(micro / 1000000, 10);
  let days = parseInt(sec / 86400, 10);
  sec %= 86400;
  let hour = parseInt( sec / 3600);
  let min  = parseInt( (sec - hour * 3600) / 60);

  let nd = new Date(1601, 1, 1);
  nd.setDate(nd.getDate() + days);
  nd.setHours(nd.getHours() + hour);
  nd.setMinutes(nd.getMinutes() + min);

  return nd.getFullYear() +'/' 
	+ digit2(nd.getMonth())+'/'
	+ digit2(nd.getDate()) 
	+ ' ' + digit2(nd.getHours())
	+ ':' + digit2(nd.getMinutes());
};

const recursePrint = function( obj ){
  if( obj.type === 'folder'){
    obj.children.forEach( recursePrint );
  } else {
    console.log( dateStr( obj.date_added) + ' | ' + obj.url + ' | ' + obj.name );
  }
}

recursePrint( objBM.roots.bookmark_bar );

