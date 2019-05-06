#ifndef _CLSUTILS_H
#define _CLSUTILS_H
#include "arduino.h"


class Cls_Utils
{
  public:
    static Cls_Utils* Instance(); //SIGLETON

    char static *fnc_ftoa(char *a, double f, int precision);
    static char *fnc_itoa(char *a, int i);
    String fncWifi_IP42String(IPAddress ipIPAddress);
    IPAddress  fncWifi_String2IP4(String sIP4);
    String  fncBldJsonStart();
    String  fncBldJsonEnd();
    String  fncBldJsonFielSetStart(bool isFirst, String szFieldSetTitle);
    String  fncBldJsonFielSetEnd();
    String  fncBldJsonFielSetAddItem(bool isFirst, String szName, String szDescription, String szValue, String szUnit, String szCssClass, String szCommands);
    String fncStringBySep(String data, char separator, int index);
  //[{"text": "on", "uri": "/mod_rel?id=0&sts=1","cssclass":"button"   },
  String  fncBldJsonCmdStart();
  String  fncBldJsonCmdEnd();
  String  fncBldJsonCmdAdd(bool isFirst, String text, String uri, String szCssClass);
  


  protected:
    Cls_Utils(void);                                 //SIGLETON
    Cls_Utils(const Cls_Utils & ) ;               //SIGLETON
    Cls_Utils &operator= (const Cls_Utils & ) ;   //SIGLETON
    ~Cls_Utils(void);                               //SIGLETON
  private:
    static Cls_Utils* m_pInstance;                 //SIGLETON
};
#endif
