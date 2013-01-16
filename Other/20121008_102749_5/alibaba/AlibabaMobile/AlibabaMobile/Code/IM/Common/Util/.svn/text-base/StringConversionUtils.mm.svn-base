#import "StringConversionUtils.h"

std::string NSStr2CStr(NSString* strContent) {	
	if (strContent == nil) {
        return "";
    } else {
		NSStringEncoding enc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000);
        return std::string([strContent cStringUsingEncoding:enc]);
    }
	
}


NSString* CStr2NSStr(const std::string& strContent) {
    
    
    
    if(strContent.empty()){
        return @"";
    }
    
	NSStringEncoding enc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000);
	NSString *str = [NSString stringWithCString:strContent.c_str() encoding:enc];
	if (str == nil) {
		str = [NSString stringWithUTF8String:strContent.c_str()];
	}

	return str;
}