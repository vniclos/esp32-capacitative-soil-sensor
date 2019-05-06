//javascripts

#ifndef _WEB_CSS_H
#define _WEB_CSS_H
const char g_HTML_Web_CSS[] PROGMEM = R"=====(
body {background-color: #555; background-image: linear-gradient(#666, #999); padding: 5px;}
#divbody { min-height:100vh; padding:1rem; max-width: 800px; margin: auto; background-color: #fff; border-radius: 15px;  border: 1px solid #73AD21;}
#menu{text-align:center; border: solid 1px #aaaaaa; padding:5px; background-color:#eeeeee;background:#dfe3ee;border-radius: 6px;margin:auto;}
div {line-height: 1.6;}
.fldtit,.fldvalue  {display:inline-table;min-width:100px; height:1.3rem;  }
.fldvalue{margin-left=1em; font-weight: bold;}
input {display:inline-block;margin-top: 8px; margin-bottom:16px; box-sizing: border-box;}

svg.cartesian {  display:flex;}
svg.cartesian > g {  transform: scaleY(-1);}
svg.cartesian > g text {    transform: scaleY(-1);}

li {margin-bottom:1em;}
.filename{min-width:18rem; margin-right:3rem}
#scnMsg{float-none;}


.of, .on{background-color:#0d0;color:#fff; font-size:12px;padding:3px;border-radius: 3px}
.of{background-color:#000;}
  fieldset { 
  margin-top:1rem;
  margin-left: 2px;
  margin-right: 2px;
  padding-top: 0.35em;
  padding-bottom: 0.625em;
  padding-left: 0.75em;
  padding-right: 0.75em;
  border: 2px groove (internal value);
  border-radius: 4px;
}


.mini {width:auto; font-size:0.8rem;padding: 2px; height:auto;width:auto; margin:0;}

button, input[type=button], input[type=submit], input[type=reset], .btn {
  -moz-box-shadow:inset 0px 1px 3px 0px #91b8b3;
  -webkit-box-shadow:inset 0px 1px 3px 0px #91b8b3;
  box-shadow:inset 0px 1px 3px 0px #91b8b3;
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #768d87), color-stop(1, #6c7c7c));
  background:-moz-linear-gradient(top, #768d87 5%, #6c7c7c 100%);
  background:-webkit-linear-gradient(top, #768d87 5%, #6c7c7c 100%);
  background:-o-linear-gradient(top, #768d87 5%, #6c7c7c 100%);
  background:-ms-linear-gradient(top, #768d87 5%, #6c7c7c 100%);
  background:linear-gradient(to bottom, #768d87 5%, #6c7c7c 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#768d87', endColorstr='#6c7c7c',GradientType=0);
  background-color:#768d87;
  -moz-border-radius:5px;
  -webkit-border-radius:5px;
  border-radius:5px;
  border:1px solid #566963;
  display:inline-block;
  cursor:pointer;
  color:#ffffff;
  font-family:Arial;
  font-size:14px;
  font-weight:bold;
  padding:4px 6px;
  text-decoration:none;
  text-shadow:0px -1px 0px #2b665e;
  margin-right:5px;
  
}
button:hover, input[type=button], input[type=submit], input[type=reset], .btn:hover {
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #6c7c7c), color-stop(1, #768d87));
  background:-moz-linear-gradient(top, #6c7c7c 5%, #768d87 100%);
  background:-webkit-linear-gradient(top, #6c7c7c 5%, #768d87 100%);
  background:-o-linear-gradient(top, #6c7c7c 5%, #768d87 100%);
  background:-ms-linear-gradient(top, #6c7c7c 5%, #768d87 100%);
  background:linear-gradient(to bottom, #6c7c7c 5%, #768d87 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#6c7c7c', endColorstr='#768d87',GradientType=0);
  background-color:#6c7c7c;
}
legend {
  display: block;
  padding: 6px;
  padding-right: 5px;
  border: solid 1px #aaaaaa;
  background-color:#eeeeee;
  background:   #dfe3ee;
  border-radius: 6px;
  font-weight:bold;
}
.btnmini
{  clear: right;
  float:none;
  }


.msg{background-color:#333; color: #fff;}
.msgred{background-color:#333; color: #f00;}
.mini {width:auto; padding: 5px;}


.loader{
  margin: 0 0 2em;
  height: 100px;
  width: 20%;
  text-align: center;
  padding: 1em;
  margin: 0 auto 1em;
  display: inline-block;
  vertical-align: top;
}

/*
  Set the color of the icon
*/
svg path,
svg rect{
  fill: #FF6700;
}

)=====";
#endif
