//
//  YCCHMapClusterController.h
//  YCCHMapClusterController
//
//  Copyright (C) 2013 Claus Höfele
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>
#import "YandexMapKit.h"

@class YCCHMapClusterAnnotation;
@protocol YCCHMapClusterControllerDelegate;
@protocol YCCHMapClusterer;
@protocol YCCHMapAnimator;

/**
 Controller to cluster annotations. Automatically updates clustering when user zooms or pans the map.
 */
@interface YCCHMapClusterController : NSObject

/** Clustered annotations. */
@property (nonatomic, copy, readonly) NSSet *annotations;
/** Map view to display clustered annotations. */
@property (nonatomic, readonly) YMKMapView *mapView;

/** Multiplier to extend visible area that's included for clustering (default: 0.5). */
@property (nonatomic) double marginFactor;
/** Cell size in [points] (default: 60). */
@property (nonatomic) double cellSize;

/** The current zoom level of the visible map region. A zoom level of 0 means that the entire map fits
 the screen width. The value increases while zooming in. */
@property (nonatomic, readonly) double zoomLevel;
/** The maximum zoom level before clustering will be disabled and each annotation on the map will
 have a unique location (default: `DBL_MAX`). */
@property (nonatomic) double maxZoomLevelForClustering;

/** The minimum number of unique locations before a cell gets clustered (default: 0). */
@property (nonatomic) NSUInteger minUniqueLocationsForClustering;

/** Delegate to configure cluster annotations. */
@property (nonatomic, weak) id<YCCHMapClusterControllerDelegate> delegate;

/** Strategy for positioning cluster annotations (default: `YCCHCenterOfMassMapClusterer`). */
@property (nonatomic, weak) id<YCCHMapClusterer> clusterer;
/** Reuse existing cluster annotations for a cell (default: `YES`). */
@property (nonatomic) BOOL reuseExistingClusterAnnotations;

/** Strategy for animating cluster annotations in and out (default: `YCCHFadeInOutMapAnimator`). */
@property (nonatomic, weak) id<YCCHMapAnimator> animator;

/** Displays the grid used for clustering. */
@property (nonatomic, getter = isDebuggingEnabled) BOOL debuggingEnabled;

/**
 Initializes the cluster controller.
 @param mapView `YMKMapView` to use to display clusters.
 */
- (instancetype)initWithMapView:(YMKMapView *)mapView;

/** 
 Adds annotations and immediately updates clustering.
 @param annotations Annotations to add.
 @param completionHandler Called when the clustering finished updating.
 */
- (void)addAnnotations:(NSArray *)annotations withCompletionHandler:(void (^)())completionHandler;

/**
 Removes annotations and immediately updates clustering.
 @param annotations Annotations to add.
 @param completionHandler Called when the clustering finished updating.
 */
- (void)removeAnnotations:(NSArray *)annotations withCompletionHandler:(void (^)())completionHandler;

/**
 Replaces annotations and immediately updates clustering.
 @param annotations Annotations to replace.
 @param completionHandler Called when the clustering finished updating.
 */
- (void)replaceAnnotations:(NSArray *)annotations withCompletionHandler:(void (^)())completionHandler;

/** 
 Zooms to the position of the cluster that contains the given annotation and selects the cluster's annotation view.
 @param annotation The annotation to look for. Uses `isEqual:` to check for a matching annotation previously added with `addAnnotations:withCompletionHandler:`.
 @param latitudinalMeters North-to-south distance used for zooming.
 @param longitudinalMeters East-to-west distance used for zooming.
 */
- (void)selectAnnotation:(id<MKAnnotation>)annotation andZoomToRegionWithLatitudinalMeters:(CLLocationDistance)latitudinalMeters longitudinalMeters:(CLLocationDistance)longitudinalMeters;

/**
 Zooms to the region that "holds" cluster annotation. Useful as clicking handler.
 */
- (void)zoomToRegionOfClusterAnnotation:(YCCHMapClusterAnnotation*)ann;

/**
 Useful to call on -viewDidAppear
 */
- (void)refreshAnnotations;

@end
