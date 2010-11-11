int i;
int iter = 1000000;
int j;

util_watch_start(withlp);
j = 0;
for( i = 0 ; i < iter ; ++i ) {
  NSLog(@"INLOOP %@", [NSString stringWithFormat: @"%ld", (long) j]);
  ++j;
 }
double withlp = util_watch_seconds(withlp);
NSLog(@"with: %.9f each: %.9f", withlp, withlp / j);

util_watch_start(withoutlp);
j = 0;
for( i = 0 ; i < iter ; ++i ) {
  ++j;
 }
double withoutlp = util_watch_seconds(withoutlp);

NSLog(@"wout: %.9f each: %.9f", withoutlp, withoutlp / j);

NSLog(@"cost per lp: %.9f on %ld iter: %.9f", withlp / j - withoutlp / j, (long) j, withlp - withoutlp);

