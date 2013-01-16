#import "AMImage.h"
#import <RestKit/RestKit.h>

NSString * const DEFAULT_IMAGE_EXT = @".jpg";

@implementation AMImage

@synthesize imageURI;
@synthesize bankImage;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMImage class]] retain];
			[self.sharedObjectMapping mapKeyPath:@"imageURI" toAttribute:@"imageURI"];
			[self.sharedObjectMapping mapKeyPath:@"bankImage" toAttribute:@"bankImage"];
        }
    }
    
    return sharedObjectMapping;
}

/**
 * 150*150
 * 
 * @param sourceImage
 * @return
 */
- (NSString *) convertSearchImageURI {
  return [self getImageName:150];
}


/**
 * 310*310
 * 
 * @param sourceImage
 * @return
 */
- (NSString *) convertSize310x310ImageURI {
  return [self getImageName:310];
}


/**
 * 220*220
 * 
 * @param sourceImage
 * @return
 */
- (NSString *) convertSize220x220ImageURI {
  return [self getImageName:220];
}

/**
 * 100*100
 * 
 * @param sourceImage
 * @return
 */
- (NSString *) convertSize100x100ImageURI {
    return [self getImageName:100];
}

/**
 * 150*150
 * 
 * @param sourceImage
 * @return
 */
- (NSString *) convertSize150x150ImageURI {
    return [self getImageName:150];
}

/**
 * 64*64
 * 
 * @param sourceImage
 * @return
 */
- (NSString *) convertSize64x64ImageURI {
  return [self getImageName:64];
}


/**
 * 100*100
 * 
 * @param sourceImage
 * @return
 */
- (NSString *) convertSummImageURI {
  return [self getImageName:100];
}

- (NSString *) getImageName:(NSInteger)imagesizetype {
    NSString * srcName = imageURI;
    if (srcName == nil || [@"" isEqualToString: srcName])
        return @"";
    if ([self bankImage]) {
        if (![[srcName lowercaseString] hasSuffix:DEFAULT_IMAGE_EXT])
            srcName = [srcName stringByAppendingString: DEFAULT_IMAGE_EXT];
        int index = [srcName rangeOfString:@"." options: NSBackwardsSearch].location;
        return [[[srcName substringToIndex: index] stringByAppendingString: [self getImageSize: imagesizetype]] stringByAppendingString: [srcName substringFromIndex :index]];
    }
    else {
        return [[srcName stringByAppendingString:@"&w="] stringByAppendingFormat: @"%d", imagesizetype];
    }
}


/**
 * @param imagesizetype
 * @return
 * @author qizhi.tangqz 
 */
- (NSString *) getImageSize:(NSInteger)imagesizetype {
  NSString * imagesize = @"";

  switch (imagesizetype) {
  case 64:
    imagesize = @".64x64";
    break;
  case 100:
    imagesize = @".summ";
    break;
  case 150:
    imagesize = @".search";
    break;
  case 220:
    imagesize = @".220x220";
    break;
  case 310:
    imagesize = @".310x310";
    break;
  }
  return imagesize;
}

- (void) dealloc {
    [imageURI release];
    [bankImage release];
    
    [super dealloc];
}

@end
