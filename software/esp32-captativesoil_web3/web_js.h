//javascripts
// validator https://jshint.com/
//https://codebeautify.org/jsviewer
#ifndef _WEB_JS_H
#define _WEB_JS_H
const char g_HTML_Web_JS[] PROGMEM = R"=====(

function fncOtaUpload() {
  var form = document.getElementById('file-form');
  var fileSelect = document.getElementById('scnOtaFileSelect');
  var fileSelectValue=fileSelect.value;
  var scnMsgFile =document.getElementById("scnMsgFile") 
  var EndWith=".esp32.bin"
  if(!fileSelectValue.endsWith(EndWith))
  {   
    EndWith="File not match with * = "+EndWith;
  alert("File "+fileSelectValue+ " not end with"+EndWith+ ". Cancel");
    return false;
    }
  var agree = confirm("Are you sure!\nDo you want update to firmware: " + fileSelectValue + " ?");
  if (!agree) {return false;}
  var uploadButton = document.getElementById('scnOtaUploadBtn');
    event.preventDefault();
    var progress = document.getElementById('progress');
    var progressdiv = document.getElementById('progressdiv');
    progress.style.display = "block";
    uploadButton.innerHTML = 'Uploading...';
    var files = fileSelect.files;
    var formData = new FormData();
    var file = files[0];
    formData.append('scnOtaFileSelect', file, file.name);
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/otaupdate', true);
    xhr.upload.onprogress = function (e) {
      fncOtaUpload_progres(e);
    }
    xhr.onload = function (e) {
      if (xhr.status === 200) {
        uploadButton.innerHTML = 'Upload';
        progressdiv.innerHTML = "<h3>Sucess</h3>";
      } else {
        alert('An error occurred!');
      }
    };
    xhr.send(formData);
  }

  function fncOtaUpload_progres(e){
      if (e.lengthComputable){
        var uploadButton = document.getElementById('scnOtaUploadBtn');
        var percentage = Math.round((e.loaded/e.total)*100);
        progress.value = percentage;
        uploadButton.innerHTML = 'Upload '+percentage+'%';
        console.log("percent " + percentage + '%' );
        if (percentage==100) {alert( "Update finished.\nYour system are rebooting\n Please wait a seconds, and them refresh your browser" );}
      }
      else{ console.log("Unable to compute progress information since the total size is unknown");}
  }
//..................
function fncRestart() {
 var agree = confirm("Are you sure you want restart ");
 if (agree) {
  var uri = "/restart";
  document.getElementById("scnDebug").innerHTML = uri;
  fncGetHtml("scnMsg", uri);
  return true;
 } else {
  fncMsg("scnMsg", "Restart canceled", false);
  return false;
 }
}
//..................
function fncDelete(FileName) {
 var agree = confirm("Are you sure you want to delete the file  " + FileName + "?");
 if (agree) {
  var uri = "/filedel?file=" + FileName;
  document.getElementById("scnDebug").innerHTML = uri;
  fncGetHtml("scnMsg", uri);
  return true;
 } else {
  fncMsg("scnMsg", "Delete", false);
  return false;
 }
}
//..................
function fncStatusGet() {
 fncGetHtml("msgStatus", "/fncStatusGet");
 return false;
}
//..................
function fncDebug() {
 fncGetHtml("scnDebug", "/fncDebug");
 return false;
}
//..................
var g_Ajax_XHR;

function fncCfggetConfig() {
 g_Ajax_XHR = fncBuildXMLHttpRequest();
 g_Ajax_XHR.onreadystatechange = fncAjax_ConfigFill;
 g_Ajax_XHR.open("GET", "configget");
 g_Ajax_XHR.send(null);
 return false;
}
//..................
function fncBuildXMLHttpRequest() {
 g_Ajax_XHR = new XMLHttpRequest();
 return g_Ajax_XHR;
}
//..................
function fncAjax_ConfigFill() {
 var valuesSharp = g_Ajax_XHR.responseText;
 document.getElementById("scnDebug").innerHTML = "Reply:" + valuesSharp;
 fncCfggetConfigFill(valuesSharp);
 return false;
}
//..................
//myVar = setTimeout(fncFillDelayed, 3000);
function fncFillDelayed() {
 fncCfggetConfig();
 return false;
}
//..................
function fncGetAjax(pURL) {
 //console.log("fncGetAjax pURL= " + pURL);
 var xhttp;
 var reply = "";
 xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
  if (xhttp.readyState == 4 && xhttp.status == 200) {
   reply = xhttp.responseText;
   document.getElementById("scnMsg").innerHTML = reply;
   return reply;
  }

 };
 xhttp.open("GET", pURL, true);
 xhttp.send();
}

function fncGetHtml(pDivTarget, pURL) {
 //console.log("pDivTarget=" + pDivTarget + "\n pURL= " + pURL);

 var xhttp;

 xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function() {
  if (xhttp.readyState == 4 && xhttp.status == 200) {
   var date = new Date();
   var vTimeDate = "" + date.toDateString() + " " + date.toLocaleTimeString();

  // console.log(vTimeDate);
   document.getElementById(pDivTarget).innerHTML = xhttp.responseText + ". At: " + vTimeDate;

  }

 };
 xhttp.open("GET", pURL, true);
 xhttp.send();
}

function fncMsg(pDivTarget, msg) {
 document.getElementById(pDivTarget).innerHTML = msg;
 return false;
}

function fncCfgSetDataloger() {
 fncCfgCfgClearBtnMsg();
 var bOk = true;
 if (fncCfgIsMinLenght("scnLoc", "scnLocMsg", "Location is empty", 10)) { bOk = false;}
 if (!bOk) {  return false; }
 alert(document.getElementById("scnInterval").value);
var select_id = document.getElementById("scnInterval");

alert(select_id.options[select_id.selectedIndex].value);
 
 var szUrl = "cfgsetdl?loc=" + document.getElementById("scnLoc").value + "&Gps=" + document.getElementById("scnGps").value + "&inteval=" + document.getElementById("scnInterval").value;
 fncCfgMsgCfg("scnMsgDlBtn", "Send: " + szUrl);
 fncGetAjax(szUrl);
 return false;
}
//.............
function fncCfgSetDateTime() {
 fncCfgCfgClearBtnMsg();
 var bOk = true;
 if (fncCfgIsMinLenght("scnDate", "scnDateMsg", "Fil date ", 10)) {
  bOk = false;
 }
 if (fncCfgIsMinLenght("scnTime", "scnTimeMsg", "Fill time", 5)) {
  bOk = false;
 }
 if (!bOk) {
  return false;
 }
 var szUrl = "cfgsetdt?date=" + document.getElementById("scnDate").value + "&time=" + document.getElementById("scnTime").value;
 fncCfgMsgCfg("scnMsgTimeBtn", "Send: " + szUrl);
 fncGetAjax(szUrl);
 return false;
}
//.............
function fncCfgSetWifi() {
 fncCfgCfgClearBtnMsg();
 var szMode = "";
 var bOk = true;
 if (document.getElementById("scnModeap").checked) {
  szMode = "ap";

  if (fncCfgIsMinLenght("scnWifiApSiid", "scnWifiApSiidMsg", "SIID Accespoint ", 10)) {
   bOk = false;
  }
  if (fncCfgIsMinLenght("scnWifiApPwd", "scnWifiApPwdMsg", "Fill password", 9)) {
   bOk = false;
  }
  if (!bOk) {
   return false;
  }
 } else {
  szMode = "ws";
  if (fncCfgIsMinLenght("scnWifiWsSiid", "scnWifiWsSiidMsg", "Fill SIID of your net", 10)) {
   bOk = false;
  }
  if (fncCfgIsMinLenght("scnWifiWSPwd", "scnWifiWSPwdMsg", "Fill Pwsd of your net", 9)) {
   bOk = false;
  }
  if (document.getElementById("scnDhcpOff").checked) {
   if (!fncCfgIsIPaddress("sncIp", "sncIpMsg", "Fill your Ip")) {
    bOk = false;
   }
   if (!fncCfgIsIPaddress("sncIpMask", "sncIpMaskMsg", "Fill your mask")) {
    bOk = false;
   }
   if (!fncCfgIsIPaddress("sncIpGate", "sncIpGateMsg", "FIll your gateway, Router")) {
    bOk = false;
   }
   if (!fncCfgIsIPaddress("sncIpDns1", "sncIpDns1Msg", "FIll your DNS1, example 8.8.8.8")) {
    bOk = false;
   }
   if (!fncCfgIsIPaddress("sncIpDns2", "sncIpDns2Msg", "FIll your DNS2, example 8.8.4.4")) {
    bOk = false;
   }
  }
  if (!bOk) {
   return false;
  }
 }
 if (document.getElementById("scnModeap").checked) {
  szMode = "ap";
 } else {
  szMode = "ws";
 }
  var szUrl="";
 szUrl = "cfgsetwifi?mode=" + szMode;
 szUrl += "&ApSiid=" + document.getElementById("scnWifiApSiid").value;
 szUrl += "&ApPwd=" + document.getElementById("scnWifiApPwd").value;
 szUrl += "&WsSiid=" + document.getElementById("scnWifiWsSiid").value;
 szUrl += "&WSPwd=" + document.getElementById("scnWifiWSPwd").value;
  var szWsDhcp="0";
 if (document.getElementById("scnDhcpOn").checked) {
  szWsDhcp = "1";
 } else {
  szWsDhcp = "0";
 }
 szUrl += "&WsDhcp=" + szWsDhcp;
 szUrl += "&WSIp=" + document.getElementById("sncIp").value;
 szUrl += "&WSMask=" + document.getElementById("sncIpMask").value;
 szUrl += "&WSGate=" + document.getElementById("sncIpGate").value;
 szUrl += "&WSDns1=" + document.getElementById("sncIpDns1").value;
 szUrl += "&WSDns2=" + document.getElementById("sncIpDns2").value;
 fncCfgMsgCfg("scnMsgWifiBtn", ("Send: " + szUrl));

 fncGetAjax(szUrl);
}

function fncStrContainsStr(strMain, strFind) {
 return (strMain.indexOf(strFind) != -1 ? true : false);
}

//-------------------------------------------------------------
function fncCfggetConfigFill(valuesSharp) {
 fncCfgDebug("fncCfggetConfigFill " + valuesSharp);
 fncCfgCfgClearBtnMsg();

 while (fncStrContainsStr(valuesSharp, "##")) {
  valuesSharp = valuesSharp.replace("##", "#");
 }

 var aValues = valuesSharp.split("#");
 //for (var i=0; i< aValues.length;i++) {alert( i+"="+ aValues[i]); }
 document.getElementById("scnLoc").value = aValues[0];
 document.getElementById("scnGps").value = aValues[1];
 document.getElementById("scnInterval").value=aValues[2];
 if (aValues[3] == "ap") {
 document.getElementById("scnModeap").checked = true;}
 else {  document.getElementById("scnModews").checked = true; }
 document.getElementById("scnWifiApSiid").value = aValues[4];
 document.getElementById("scnWifiApPwd").value = aValues[5];
 document.getElementById("scnWifiWsSiid").value = aValues[6];
 document.getElementById("scnWifiWSPwd").value = aValues[7];
 if (aValues[8] == "1") {document.getElementById("scnDhcpOn").checked = true;}
 else {document.getElementById("scnDhcpOff").checked = true;}
 document.getElementById("sncIp").value = aValues[9];
 document.getElementById("sncIpMask").value = aValues[10];
 document.getElementById("sncIpGate").value = aValues[11];
 document.getElementById("sncIpDns1").value = aValues[12];
 document.getElementById("sncIpDns2").value = aValues[13];
 document.getElementById("scnDate").value = aValues[14];
 document.getElementById("scnTime").value = aValues[15];
 document.getElementById("scnWifiApSiidEnd").value = aValues[16];
 document.getElementById("scnDebug").innerHTML = valuesSharp;
}

function fncCfgTogglePwds(fieldid, oFrom) {
 var temp = document.getElementById(fieldid);
 if (temp.type === "password") {
  temp.type = "text";
  oFrom.innerHTML = "hide";
 } else {
  temp.type = "password";
  oFrom.innerHTML = "show";
 }
}

function fncCfgMsgCfg(scnFieldId, Msg) {
 document.getElementById(scnFieldId).innerHTML = Msg;
}

function fncCfgDebug(msg) {
 document.getElementById("scnDebug").innerHTML = msg;
}

function fncCfgCfgClearBtnMsg() {
try {
 document.getElementById("scnDebug").innerHTML = "";
 document.getElementById("scnMsg").innerHTML = "";
//document.getElementById("scnInterval").value=10;
 document.getElementById("scnGpsMsg").innerHTML = "";
 document.getElementById("scnDateMsg").innerHTML = "";
 document.getElementById("scnTimeMsg").innerHTML = "";
 document.getElementById("scnWifiWSPwdMsg").innerHTML = "";
 document.getElementById("scnDebug").innerHTML = "";
 document.getElementById("scnMsgDlBtn").innerHTML = "";
 document.getElementById("scnMsgTimeBtn").innerHTML = "";
 document.getElementById("scnDebug").innerHTML = "";
 document.getElementById("scnMsgWifiBtn").innerHTML = "";
 document.getElementById("sncIpMsg").innerHTML = "";
 document.getElementById("sncIpMaskMsg").innerHTML = "";
 document.getElementById("sncIpGateMsg").innerHTML = "";
 document.getElementById("sncIpDns1Msg").innerHTML = "";
 document.getElementById("sncIpDns2Msg").innerHTML = "";
 document.getElementById("scnLocMsg").innerHTML = "";
 }
 catch(error)
 { console.log(error); }
}

function fncCfgIsIPaddress(fldId, fldIdMsg, msg) {
 var ipformat = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
 var fld = document.getElementById(fldId);

 if (fld.value.match(ipformat)) {
  fncMsgError(fldIdMsg, "");
  fld.focus();
  return true;
 } else {
  fncMsgError(fldIdMsg, msg);
  return false;
 }
}

function fncCfgIsMinLenght(idFldChk, idFldMsg, Msg, MinLenght) {
 var isEmpty = false;
 var oValue = document.getElementById(idFldChk).value.trim();
 var oMsg = document.getElementById(idFldMsg);
 oMsg.value = "";
 oMsg.innerHTML = "";
 if (oValue.length < MinLenght) {
  var msg = " " + Msg + " or less than " + MinLenght;
  fncMsgError(idFldMsg, msg);
  isEmpty = true;
 } else {
  fncMsgError(idFldMsg, "");
  isEmpty = false;
 }
 return isEmpty;
}

function fncMsgError(idFldMsg, msg) {
 var oMsg = document.getElementById(idFldMsg);
 oMsg.innerHTML = msg;
 if (msg == "") {
  oMsg.style.display = true;
  oMsg.innerHTML = "&#x2714;";
  oMsg.style.backgroundColor = "#fff";
  oMsg.style.color = "#090";
 } else {
  oMsg.style.display = true;
  oMsg.style.backgroundColor = "#900";
  oMsg.style.color = '#fff';
 }
}
function fncGpsNavigatorGetInner()
{
  var szurl="http://www.google.com/maps/place/"+document.getElementById("scnGps").innerHTML;
   //console.log("open= " + szurl);
  window.open(szurl);
  }
function fncGpsNavigatorGet()
{
  //http://www.google.com/maps/place/49.46800006494457,17.11514008755796
  var szurl="http://www.google.com/maps/place/"+document.getElementById("scnGps").value;
   //console.log("open= " + szurl);
  window.open(szurl);
  }
//---------------



)=====";
#endif
