#include "Cls_Utils.h"
Cls_Utils* Cls_Utils::m_pInstance = 0;//  //SIGLETON

Cls_Utils* Cls_Utils::Instance () // SINGLETON
{
  if (m_pInstance == 0)  // ¿Es la primera llamada?
  {
    m_pInstance = new Cls_Utils; // Creamos la instancia
  }
  return m_pInstance; // Retornamos la direccion de la instancia
}

Cls_Utils::Cls_Utils(void) {}
Cls_Utils::~Cls_Utils(void) {}

//=============================================================
// *Cls_Utils::Cls_Utils::toa(char array[])
// Chek if array content is not empty
// and is not all spaces
// and in not cero
// used for check consistence values 
// recived by seria or other sources
//=============================================================


//=============================================================
// *Cls_Utils::fnc_ftoa(char *a, double f, int precision)
// Convierte un float en char*
// Parametros
// a Puntero a array
// f =Float
// precision= numero de decimales
//=============================================================


char *Cls_Utils::fnc_ftoa(char *a, double f, int precision)
{
  long p[] = {0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
  char *ret = a;
  long heiltal = (long)f;
  itoa(heiltal, a, 10);
  while (*a != '\0') a++;
  *a++ = '.';
  long desimal = abs((long)((f - heiltal) * p[precision]));
  itoa(desimal, a, 10);
  return ret;
}


//=============================================================
// char* Cls_Utils::fnc_itoa(char *a, int i)
//  Cls_Utils::fncWifi_IP42String(IPAddress ipIPAddress)
// Convierte un int en char*
// Parametros
// a= char pointer a array
// i= entero
//=============================================================
char* Cls_Utils::fnc_itoa(char *a, int i) {

  itoa(i, a, 10);
  return a;

}


//===========================================================
// Cls_Utils::fncWifi_IP42String(IPAddress ipIPAddress)7
// Convierte un Ipaddres en string
//===========================================================
String  Cls_Utils::fncWifi_IP42String(IPAddress ipIPAddress)
{

#ifdef DEBUG
  Serial.println("*** ClsStd_NetWifiMng::fncWifi_IP42String(IPAddress sIPAddress)");

#endif

  String zbuff = "";
  zbuff = String (ipIPAddress[0]) + "." + String (ipIPAddress[1]) + "." + String (ipIPAddress[2]) + "." + String (ipIPAddress[3]) + ".";
  return zbuff;

}

//===========================================================
// IPAddress ClsStd_NetWifiMng::fncWifi_String2IP4()
// convierte un string en ipaddress
//===========================================================
IPAddress  Cls_Utils::fncWifi_String2IP4(String sIPAddress)
{
#ifdef DEBUG
  Serial.println("*** ClsStd_NetWifiMng::fncWifi_String2IP4(" + sIPAddress + ")");

#endif
  //char* ptr;
  short int siA = 0; // varialbles comodin
  short int siB = 0;
  short int siC = 0;
  short int siD = 0;
  short int iPos1 = 0;
  short int iPos2 = 0;
  short int iPos3 = 0;
  iPos1 = sIPAddress.indexOf('.');
  iPos2 = sIPAddress.indexOf('.', iPos1 + 1);
  iPos3 = sIPAddress.indexOf('.', iPos2 + 1);
  siA = sIPAddress.substring(0, iPos1).toInt();
  siB = sIPAddress.substring(iPos1 + 1, iPos2).toInt();
  siC = sIPAddress.substring(iPos2 + 1, iPos3).toInt();
  siD = sIPAddress.substring(iPos3 + 1).toInt();
  return IPAddress(siA, siB, siC, siD);
}
//**********************************************************
// LA Siguientes funciones sirven para formatear String
// en formato JSON
//**********************************************************


// ========================================================
// Cls_Utils::Cls_Utils::fncBldJsonStart()
// Incia el JSON COMO ARRAY
//=========================================================
String   Cls_Utils::Cls_Utils::fncBldJsonStart()
{
  return "[";
}
// ========================================================
// Cls_Utils::Cls_Utils::fncBldJsonEnd()
// FINALIZA el JSON  ARRAY
//=========================================================
String   Cls_Utils::Cls_Utils::fncBldJsonEnd()
{
  return "]";
}
// ========================================================
// Cls_Utils::Cls_Utils::fncBldJsonEnd()
// INICIA UNA FILA O CONJUNTO NUEVO
// is Firt =true no añade la coma separadora
// szFieldSetTitle= Nombe o titulo de la nueva fila
// o conjunto
// en el html se transforma en una caja con titulo
//=========================================================
String   Cls_Utils::Cls_Utils::fncBldJsonFielSetStart(bool isFirst, String szFieldSetTitle)
{
  String szReturn = "";
  if (!isFirst) {
    szReturn = ", ";
  }
  szReturn += "{\"fieldset\": \"" + szFieldSetTitle + "\", \"items\": [";
  return szReturn;
}
// ========================================================
// String  Cls_Utils::fncBldJsonFielSetEnd()
// finaliza una fila o conjunto
// ========================================================
String  Cls_Utils::fncBldJsonFielSetEnd()
{
  return  "]}";
}
// ========================================================
//  Cls_Utils::fncBldJsonFielSetAddItem(bool isFirst, String szName, String szDescription, String szValue, String szUnit, String szCssClass, String szCommands)
// agrega los datos de una fila o conjunto
// String szCommands es en si otra fila que contiene comandos url
// ========================================================
String  Cls_Utils::fncBldJsonFielSetAddItem(bool isFirst, String szName, String szDescription, String szValue, String szUnit, String szCssClass, String szCommands)
{
  String szReturn = "{";
  if (!isFirst) {
    szReturn = ", " + szReturn;
  }
  szReturn += "\"name\": \"" + szName + "\", ";
  szReturn += "\"description\": \"" + szDescription + "\", ";
  szReturn += "\"value\": \"" + szValue + "\", ";
  szReturn += "\"uni\": \"" + szUnit + "\",";
  szReturn += "\"cssclass\": \"" + szCssClass + "\"";
  if (szCommands != ""){
  szReturn += (",\"commands\": " + szCommands);
  }
  szReturn += "}";
  return szReturn;
}

//___________________________________________________________

String Cls_Utils::fncStringBySep(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
/*
___________________________________________________________

//[{"text": "on", "uri": "/mod_rel?id=0&sts=1","cssclass":"button"   },
String  fncBldJsonCmdStart();
String  fncBldJsonCmdEnd();
String  fncBldJsonCmdFielSetStart(bool isFirst, String szFieldSetTitle);
String  fncBldJsonCmdFielSetEnd();
String  fncBldJsonCmdFielSetAddItem(bool isFirst, String szName, String szDescription, String szValue, String szUnit, String szCssClass, String szCommands);
___________________________________________________________

*/













// ========================================================
// Cls_Utils::Cls_Utils::fncBldJsonStart()
// Incia el JSON COMO ARRAY
//=========================================================
String   Cls_Utils::Cls_Utils::fncBldJsonCmdStart()
{
  return "[";
}
// ========================================================
// Cls_Utils::Cls_Utils::fncBldJsonEnd()
// FINALIZA el JSON  ARRAY
//=========================================================
String   Cls_Utils::Cls_Utils::fncBldJsonCmdEnd()
{
  return "]";
}
// ========================================================
// Cls_Utils::Cls_Utils::fncBldJsonCmdAddItem()
// Devuelve el array json de una orden. un comando, 
// Parametros
// szText="Texto" aparece en html y sirve de explicación
// ejemplos: On, Off, Encender, Apagar
// szUri=Url que se tiene que enviar al nodo para que 
// ejecute la orden
// ejemplos: 
// /mod_rel?id=0&sts=1 (Poner el rele a 1)
// /mod_rel?id=0&sts=0 (Poner el rele a 0)
// /mod_temperature?value=30 (Poner la temperatura a 30) 
// szCssClass Clase que se utiliza en Html para formatear
// la orden, Ejemplo button, 
//========================================================
//{"text": "on", "uri": "/mod_rel?id=0&sts=1","cssclass":"button" 
String  Cls_Utils::fncBldJsonCmdAdd(bool isFirst, String szText, String szUri, String szCssClass)
{
  String szReturn = "{";
  if (!isFirst) {
    szReturn = ", " + szReturn;
  }
  szReturn += "\"text\": \"" + szText + "\", ";
  szReturn += "\"uri\": \"" + szUri + "\", ";
  szReturn += "\"cssclass\": \"" + szCssClass + "\"";
  szReturn += "}";
  return szReturn;
}
