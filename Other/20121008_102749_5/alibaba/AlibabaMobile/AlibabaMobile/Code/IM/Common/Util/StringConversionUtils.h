#import <string>
#import <Foundation/NSString.h>

std::string NSStr2CStr(NSString* strContent);
NSString* CStr2NSStr(const std::string& strContent);