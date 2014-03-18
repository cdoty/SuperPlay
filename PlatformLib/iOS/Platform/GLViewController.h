#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface GLViewController : UIViewController
{
}

// View did load callback
- (void) viewDidLoad;

// stop rotation to portrait views
- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)_interfaceOrientation;

@end
