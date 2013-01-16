#import "AMAppVersion.h"
#import <RestKit/RestKit.h>

@implementation AMAppVersion

@synthesize identifier = _identifier;
@synthesize platform = _platform;
@synthesize version = _version;
@synthesize versionType = _versionType;
@synthesize changelog = _changelog;
@synthesize gmtRelease = _gmtRelease;
@synthesize downloadSize = _downloadSize;
@synthesize downloadUrl = _downloadUrl;
@synthesize md5Checksum = _md5Checksum;
@synthesize isVersionAvailable = _isVersionAvailable;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
			sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMAppVersion class]] retain];
			[sharedObjectMapping mapKeyPath:@"id" toAttribute:@"identifier"];
			[sharedObjectMapping mapKeyPath:@"platform" toAttribute:@"platform"];
			[sharedObjectMapping mapKeyPath:@"version" toAttribute:@"version"];
			[sharedObjectMapping mapKeyPath:@"versionType" toAttribute:@"versionType"];
			[sharedObjectMapping mapKeyPath:@"changelog" toAttribute:@"changelog"];
			[sharedObjectMapping mapKeyPath:@"gmtRelease" toAttribute:@"gmtRelease"];
			[sharedObjectMapping mapKeyPath:@"downloadSize" toAttribute:@"downloadSize"];
			[sharedObjectMapping mapKeyPath:@"downloadUrl" toAttribute:@"downloadUrl"];
			[sharedObjectMapping mapKeyPath:@"md5Checksum" toAttribute:@"md5Checksum"];
			[sharedObjectMapping mapKeyPath:@"newVersionAvailable" toAttribute:@"isVersionAvailable"];
        }
    }
    
    return sharedObjectMapping;
}

- (void) dealloc {
  [_identifier release];
  [_platform release];
  [_version release];
  [_versionType release];
  [_changelog release];
  [_downloadUrl release];
  [_md5Checksum release];
  [_gmtRelease release];
  [_downloadSize release];
  [_isVersionAvailable release];
  
  [super dealloc];
}

@end
