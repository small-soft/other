#import "AMFeature.h"

@implementation AMFeature

@synthesize identifier = _identifier ;
@synthesize name = _name;
@synthesize values = _values;

- (NSString *) description {
  return [[NSString stringWithFormat:@"feature:{id:%@,name:%@}", self.identifier, self.name] autorelease];
}

- (void) dealloc {
  [_identifier release];
  [_name release];
  [_values release];
  
  [super dealloc];
}

@end
