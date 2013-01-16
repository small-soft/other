#import "AMSuggestWord.h"

@implementation AMSuggestWord

@synthesize word = _word;
@synthesize total = _total;

- (NSString *) description {
  return [NSString stringWithFormat:@"suggestword:{word:%@,total:%d}", self.word, self.total];
}

- (void) dealloc {
  [_word release];
  [_total release];
  
  [super dealloc];
}

@end
