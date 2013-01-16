#import "AMOfferStatus.h"

@implementation AMOfferStatus
@synthesize name = _name;
@synthesize type = _type;

+ (RKObjectMapping *)sharedObjectMapping {
    static RKObjectMapping* sharedObjectMapping;
    @synchronized (self) {
        if (!sharedObjectMapping) {
            sharedObjectMapping = [[RKObjectMapping mappingForClass:[AMOfferStatus class]] retain];
            [sharedObjectMapping mapKeyPath:@"offerStatus" toAttribute:@"name"];
        }
    }
    
    return sharedObjectMapping;
}


-(NSString*) description {
    return [self description : _type];
}

-(NSString*) description: (NSInteger) type {
    switch (type) {
        case AMMEMBER_EXPIRED:
            return @"MEMBER_EXPIRED";
        case AMAUTO_EXPIRED:
            return @"AUTO_EXPIRED";
        case AMEXPIRED:
            return @"EXPIRED";
        case AMMEMBER_DELETED:
            return @"MEMBER_DELETED";
        case AMPUBLISHED:
            return @"PUBLISHED";
        case AMMODIFIED:
            return @"MODIFIED";
        case AMNEW:
            return @"NEW";
        case AMDELETED:
            return @"DELETED";
        case AMTBD:
            return @"TBD";
        case AMAPPROVED:
            return @"APPROVED";
        case AMAUDITING:
            return @"AUDITING";
        case AMUNTREAD:
            return @"UNTREAD";
        case AMUNKNOWN:
            return @"UNKNOWN";
    }
    return nil;
}

-(NSInteger) valueOf: (NSString *)text {
    if (text) {
        if ([text isEqualToString:@"MEMBER_EXPIRED"])
            return AMMEMBER_EXPIRED;
        else if ([text isEqualToString:@"AUTO_EXPIRED"])
            return AMAUTO_EXPIRED;
        else if ([text isEqualToString:@"EXPIRED"])
            return AMEXPIRED;
        else if ([text isEqualToString:@"MEMBER_DELETED"])
            return AMMEMBER_DELETED;
        else if ([text isEqualToString:@"PUBLISHED"])
            return AMPUBLISHED;
        else if ([text isEqualToString:@"MODIFIED"])
            return AMMODIFIED;
        else if ([text isEqualToString:@"NEW"])
            return AMNEW;
        else if ([text isEqualToString:@"DELETED"])
            return AMDELETED;
        else if ([text isEqualToString:@"TBD"])
            return AMTBD;
        else if ([text isEqualToString:@"APPROVED"])
            return AMAPPROVED;
        else if ([text isEqualToString:@"AUDITING"])
            return AMAUDITING;
        else if ([text isEqualToString:@"UNTREAD"])
            return AMUNTREAD;
    }
    
    return AMUNKNOWN;
}

-(NSInteger) valueOf  {
    return [self valueOf: self.name];
}

-(void) dealloc {
    [_name release];
	
    [super dealloc];
}

@end


