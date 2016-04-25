/*
        Problem:        E
        Description:    ray intersection
        Class:          geometric
        Subclass:       linear
        Algorithm:      direct
        Author:         Ondrej Karny
        Date:           1998-Apr-03
*/
/*
 * ACM International Collegiate Programming Contest Finals 1989
 *
 * Problem E - Robot Crash
 *
 * Example solution
 *
 * Note:
 *
 * Fixes in original problem description include clarification of the
 * point of collision.
 *
 * Algorithm:
 *
 * for each pair of robots do
 *  read left gun data
 *  read right gun data
 *  compute hit point
 *  compute all relevant line segments
 *  intersect line segments and minimize time delta as well as x
 *  write result
 *
 *
 */

#include <stdio.h>

#include <math.h>

#ifdef DEBUG
#include <assert.h>
#define ASSERT( condition ) assert( condition )
#else
#define ASSERT( condition )
#endif

#ifndef M_PI
#ifdef PI
#define M_PI PI
#else                           /*ndef PI */
#define M_PI 3.14159265358979323846
#endif                          /*ndef PI */
#endif                          /*ndef M_PI */

#define MAX_DELAY 0.5
#define MAX_Y 10.0

#ifndef INFINITY
#define
#define INFINITY 10.0e10
#endif
#define EPSILON 1E-7    //0.0001

#define RADIANS( angle ) (( angle ) * M_PI / 180.0 )

typedef struct _Gun
{
    double x;
    double y;
    double angle;
    double speed;
    double xSpeed;
    double ySpeed;
} Gun;

typedef struct _Segment
{
    double x;
    double y;
    double dx;
    double dy;
    double start;
    double end;
} Segment;


static Gun leftGun;
static Gun rightGun;
static int collision;
static double collisionX;
static double collisionY;

#define FIXME( a ) printf a

#ifdef DEBUG

/*
 * Compute robot's position for given time.
 *
 */
static void positionFromTime(const Gun * gun, double time, double *x, double *y)
{
    double u;
    double v;

    u = gun->x + time * gun->xSpeed;
    v = gun->y + time * gun->ySpeed;
    if (v >= 0.0)
    {
        v = fmod(v, 2 * MAX_Y);
        if (v > MAX_Y)
        {
            v = 2 * MAX_Y - v;
        }
    }
    else
    {
        v = fmod(-v, 2 * MAX_Y);        /* /FIXME: Is that necessary? */
        if (v > MAX_Y)
        {
            v = 2 * MAX_Y - v;
        }
    }
    *x = u;
    *y = v;
}

/*
 * Compute time for given gun and position.
 *
 */
static double timeFromPosition(const Gun * gun, double x, double y)
{
    double result;

    result = (x - gun->x) / gun->xSpeed;
#ifdef DEBUG
    {
        double u;
        double v;

        positionFromTime(gun, result, &u, &v);
        ASSERT(fabs(x - u) < EPSILON);
        ASSERT(fabs(y - v) < EPSILON);
    }                           /*eob */
#endif
    return result;
}

#endif                          /*def DEBUG */

/*
 * Used by function segmentsFromTime().
 * Adds successive segment in time behind
 * the segment currently computed.
 *
 */
static void addSuccessive(const Segment * segment)
{
    Segment *next;

    next = (Segment *) (segment + 1);
/*the succesive segment is reversed*/
    next->x = segment->x;
    next->dx = segment->dx;
    next->dy = -(segment->dy);
    next->start = segment->end;
    if (segment->dy > 0.0)
    {
        ASSERT(next->dy < -EPSILON);
        /*this segment goes up, next is top-bottom */
        next->y = MAX_Y - next->dy * next->start;
        next->end = (0.0 - next->y) / next->dy;
    }
    else
    {
        ASSERT(next->dy > EPSILON);
        /*this segment goes down, next is bottom-top */
        next->y = 0.0 - next->dy * next->start;
        next->end = (MAX_Y - next->y) / next->dy;
    }
}

/*
 * Used by function segmentsFromTime().
 * Adds previous segment in time and stores
 * it in array element before the parameter.
 *
 */
static void addPrevious(const Segment * segment)
{
    Segment *prev;

    prev = (Segment *) (segment - 1);
/*the previous segment is reversed*/
    prev->x = segment->x;
    prev->dx = segment->dx;
    prev->dy = -(segment->dy);
    prev->end = segment->start;
    if (segment->dy > 0.0)
    {
        ASSERT(prev->dy < -EPSILON);
        /*this segment goes up, previous is top-bottom */
        prev->y = 0.0 - prev->dy * prev->end;
        prev->start = (MAX_Y - prev->y) / prev->dy;
    }
    else
    {
        ASSERT(prev->dy > EPSILON);
        /*this segment goes down, previous is bottom-top */
        prev->y = MAX_Y - prev->dy * prev->end;
        prev->start = (0.0 - prev->y) / prev->dy;
    }
}

/*
 * Compute line segment for given gun and time.
 * Also compute previous and successive segments
 * if it does make sense.
 *
 */
static void segmentsFromTime(const Gun * gun, double time, Segment * segment)
{
    double x;
    double y;

    ASSERT(gun);
    ASSERT(segment);
    ASSERT(time > 0.0);
/*segment defaults*/
    segment->x = gun->x;
    segment->y = gun->y;
    segment->dx = gun->xSpeed;
    segment->dy = gun->ySpeed;
/*compute position at given time*/
    x = gun->x + time * gun->xSpeed;
    y = gun->y + time * gun->ySpeed;
    if (y >= 0.0)
    {
        if (y <= MAX_Y)
        {
            /*no bounces at begin - simply goes from gun to the given point */
            ASSERT(y > EPSILON);
            ASSERT(y < MAX_Y - EPSILON);
            segment->start = 0.0;
            if (segment->dy != 0.0)
            {
                /*isn't horizontal, so the segment must end anywhere */
                ASSERT(fabs(segment->dy) > EPSILON);
                ASSERT(fabs(segment->y - MAX_Y) > EPSILON);
                if (segment->dy > 0.0)
                {
                    segment->end = (MAX_Y - segment->y) / segment->dy;
                }
                else
                {
                    segment->end = (0.0 - segment->y) / segment->dy;
                }
                ASSERT(segment->end < INFINITY);
                addSuccessive(segment);
                /*there's no previous segmet */
            }
            else
            {
                /*the segment is exactly horizontal, no previous, no next */
                segment->end = INFINITY;
            }
        }
        else
        {
            double realY;

            /*there're some bounces between begin and the desired segment */
            /*but the first bounce is on top edge, so the dy > 0.0 */
            ASSERT(segment->dy > EPSILON);
            realY = fmod(y, 2 * MAX_Y);
            if (realY > MAX_Y)
            {
                /*the segment is top-bottom segment */
                segment->dy = -(segment->dy);
                realY = 2 * MAX_Y - realY;
                segment->y = realY - segment->dy * time;
                ASSERT(fabs((segment->y + segment->dy * time) - realY) <
                    EPSILON);
                segment->start = (MAX_Y - segment->y) / segment->dy;
                segment->end = -segment->y / segment->dy;
                ASSERT(segment->start <= time);
                ASSERT(segment->end >= time);
            }
            else
            {
                /*the segment is bottom-top segment */
#if 0
                /* this equation could be written more readibly */
                segment->y -= (2 * MAX_Y) * (int)(y / (2 * MAX_Y));
#else                           /* 0 */
                segment->y = realY - segment->dy * time;
#endif                          /* 0 */
                ASSERT(fabs((segment->y + segment->dy * time) - realY) <
                    EPSILON);
                segment->start = -segment->y / segment->dy;
                segment->end = (MAX_Y - segment->y) / segment->dy;
                ASSERT(segment->start <= time);
                ASSERT(segment->end >= time);
            }
            addPrevious(segment);
            addSuccessive(segment);
        }
    }
    else
    {
        double realY;

        /*there're some bounces between begin and the desired segment */
        /*but I know the first bounce is on bottom edge, so the dy < 0.0 */
        ASSERT(segment->dy < -EPSILON);
        realY = fmod(-y, 2 * MAX_Y);
        if (realY > MAX_Y)
        {
            /*top-bottom segment */
            realY = 2 * MAX_Y - realY;
            segment->y = realY - segment->dy * time;
            ASSERT(fabs((segment->y + segment->dy * time) - realY) < EPSILON);
            segment->start = (MAX_Y - segment->y) / segment->dy;
            segment->end = -segment->y / segment->dy;
            ASSERT(segment->start <= time);
            ASSERT(segment->end >= time);
        }
        else
        {
            /*bottom-top segment, flip the dy */
            segment->dy = -(segment->dy);
            segment->y = realY - segment->dy * time;
            ASSERT(fabs((segment->y + segment->dy * time) - realY) < EPSILON);
            segment->start = -segment->y / segment->dy;
            segment->end = (MAX_Y - segment->y) / segment->dy;
            ASSERT(segment->start <= time);
            ASSERT(segment->end >= time);
        }
        addSuccessive(segment);
        addPrevious(segment);
    }
}

/*
 * Try to intersect two line segments,
 * given their parametric equation and
 * parameter constraints. Return non-zero
 * if the segments intersect.
 *
 */
static int intersectSegments(const Segment * left,
    const Segment * right, double *x, double *y, double *t)
{
    double u;
    double v;
    double det;

    det = left->dy * right->dx - left->dx * right->dy;
    if (fabs(det) < 1e-6)
    {
        det = 0.0;
    }
    ASSERT((det == 0.0) || (fabs(det) > EPSILON));
    if (det == 0.0)
    {
        det = left->dx * (right->y - left->y) - left->dy * (right->x - left->x);
        if (fabs(det) < 1e-6)
        {
            det = 0.0;
        }
        ASSERT((det == 0.0) || (fabs(det) > EPSILON));
        if (det == 0.0)
        {
            double v;

            v = (left->x - right->x) / (right->dx - left->dx);
            ASSERT(fabs(v - left->start) > EPSILON);
            ASSERT(fabs(v - left->end) > EPSILON);
            ASSERT(fabs(v - right->start) > EPSILON);
            ASSERT(fabs(v - right->end) > EPSILON);
            if ((v > left->start) &&
                (v < left->end) && (v > right->start) && (v < right->end))
            {
                *t = 0.0;
                *x = left->x + left->dx * v;
                *y = left->y + left->dy * v;
#ifdef DEBUG
                {
                    double x2;
                    double y2;

                    x2 = right->x + right->dx * v;
                    y2 = right->y + right->dy * v;
                    ASSERT(fabs(*x - x2) < EPSILON);
                    ASSERT(fabs(*y - y2) < EPSILON);
                }               /*eob */
#endif                          /*def DEBUG */
                return 1;
            }
            FIXME(("They are colinear and I have to minimize the time delta "));
            return 0;
        }
        else
        {
            /*they're parallel */
            return 0;
        }
    }
    else
    {
        double dx;
        double dy;

        dx = (right->y - left->y) * right->dx -
            (right->x - left->x) * right->dy;
        dy = left->dx * (right->y - left->y) - left->dy * (right->x - left->x);
        u = dx / det;
        v = dy / det;
        ASSERT(fabs(u - left->start) > EPSILON);
        ASSERT(fabs(u - left->end) > EPSILON);
        ASSERT(fabs(v - right->start) > EPSILON);
        ASSERT(fabs(v - right->end) > EPSILON);
        if ((u > left->start) &&
            (u < left->end) && (v > right->start) && (v < right->end))
        {
            *t = fabs(u - v);
            *x = left->x + left->dx * u;
            *y = left->y + left->dy * u;
#ifdef DEBUG
            {
                double x2;
                double y2;

                x2 = right->x + right->dx * v;
                y2 = right->y + right->dy * v;
                ASSERT(fabs(*x - x2) < EPSILON);
                ASSERT(fabs(*y - y2) < EPSILON);
            }                   /*eob */
#endif                          /*def DEBUG */
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

/*
 * Compute the 'passing point', time value
 * use to create array of line segments for
 * both the robots and then try to intersect
 * the segments. Sets collision variable
 * and collisionX/Y coordinates.
 *
 */
static void evaluate(const Gun * left, const Gun * right)
{
    double distance;
    double hitTime;

    distance = right->x - left->x;
    ASSERT(distance > EPSILON);
    hitTime = distance / (left->xSpeed - right->xSpeed);
#ifdef DEBUG
    {
        double leftPos;
        double rightPos;

        leftPos = left->x + hitTime * left->xSpeed;
        rightPos = right->x + hitTime * right->xSpeed;
        ASSERT(fabs(leftPos - rightPos) < EPSILON);
    }                           /*eob */
#endif                          /*def DEBUG */
    {
        Segment leftSegments[3];
        Segment rightSegments[3];
        int loLeft;
        int loRight;
        int hiLeft;
        int hiRight;

        segmentsFromTime(left, hitTime, leftSegments + 1);
        segmentsFromTime(right, hitTime, rightSegments + 1);
        loLeft = 1;
        hiLeft = 1;
        loRight = 1;
        hiRight = 1;
        ASSERT(fabs((hitTime - leftSegments[1].start) - MAX_DELAY) > EPSILON);
        ASSERT(fabs((leftSegments[1].end - hitTime) - MAX_DELAY) > EPSILON);
        ASSERT(fabs((hitTime - rightSegments[1].start) - MAX_DELAY) > EPSILON);
        ASSERT(fabs((rightSegments[1].end - hitTime) - MAX_DELAY) > EPSILON);
        if ((leftSegments[1].start > hitTime - MAX_DELAY) &&
            (leftSegments[1].start > 0.0))
        {
            loLeft = 0;
        }
        if ((rightSegments[1].start > hitTime - MAX_DELAY) &&
            (rightSegments[1].start > 0.0))
        {
            loRight = 0;
        }
        if (leftSegments[1].end < hitTime - MAX_DELAY)
        {
            hiLeft = 2;
        }
        if (rightSegments[1].end < hitTime - MAX_DELAY)
        {
            hiRight = 2;
        }
        {
            double x;
            double y;
            double time;
            double bestTime;

            bestTime = INFINITY;
            while (loLeft <= hiLeft)
            {
                int right;

                for (right = loRight; right <= hiRight; right++)
                {
                    if (intersectSegments(leftSegments + loLeft,
                            rightSegments + right, &x, &y, &time))
                    {
                        ASSERT(fabs(time - MAX_DELAY) > EPSILON);
                        if (time <= MAX_DELAY)
                        {
                            ASSERT((fabs(bestTime - time) > EPSILON) ||
                                (bestTime == time));
                            collision = 1;
                            if (time < bestTime)
                            {
                                bestTime = time;
                                collisionX = x;
                                collisionY = y;
                            }
                            else if (time == bestTime)
                            {
                                if (x < collisionX)
                                {
                                    collisionX = x;
                                    collisionY = y;
                                }
                            }
                        }
                    }
                }
                loLeft++;
            }
        }                       /*eob */
    }                           /*eob */
}

/*
 * Compute the move vector for the
 * given gun. Also compute first bounce
 * time and bounce period.
 *
 */
static void setupGun(Gun * gun)
{
    double angle;

    angle = RADIANS(gun->angle);
    gun->xSpeed = gun->speed * cos(angle);
    gun->ySpeed = gun->speed * sin(angle);
}

int main(int argc, const char **argv)
{
    unsigned int problemId;

    problemId = 1;
    for (;; problemId++)
    {
        int result;

        result = fscanf(stdin, "%lf %lf %lf %lf", &(leftGun.x),
            &(leftGun.y), &(leftGun.angle), &(leftGun.speed));
        ASSERT(EOF < 0);
        if (result < 0)
        {
            break;
        }
        ASSERT(result == 4);
        ASSERT(leftGun.y >= 0.0);
        ASSERT(leftGun.y <= MAX_Y);
        ASSERT((leftGun.angle <= 85.0) && (leftGun.angle >= -85.0));
        ASSERT(leftGun.speed > 0.0);
        result = fscanf(stdin, "%lf %lf %lf %lf", &(rightGun.x),
            &(rightGun.y), &(rightGun.angle), &(rightGun.speed));
        ASSERT(result == 4);
        ASSERT(rightGun.y >= 0.0);
        ASSERT(rightGun.y <= 10.0);
        ASSERT(((rightGun.angle >= -180.0) && (rightGun.angle <= -95.0)) ||
            ((rightGun.angle >= 95.0) && (rightGun.angle <= 180.0)));
        ASSERT(rightGun.speed > 0.0);
        fprintf(stdout, "Robot Problem #%u: ", problemId);
        collision = 0;
        if (leftGun.x > rightGun.x)
        {
            /* they simply can't collide */
        }
        else
        {
            if (leftGun.x == rightGun.x)
            {
                if (leftGun.y == rightGun.y)
                {
                    collision = 1;
                    collisionX = leftGun.x;
                    collisionY = leftGun.y;
                }
                else
                {
                    /* they simply can't collide */
                }
            }
            else
            {
                /* shoot them against each other and test collision */
                setupGun(&leftGun);
                setupGun(&rightGun);
                evaluate(&leftGun, &rightGun);
            }
        }
        if (collision)
        {
            fprintf(stdout, "Robots collide at (%.2f,%.2f)\n\n",
                collisionX, collisionY);
#ifdef DEBUG
            {
                double result;
                double above;
                double beyond;

#define tworound( value ) floor(( value ) * 100.0 + 0.5 )

                result = collisionX;
                above = tworound(collisionX + EPSILON);
                beyond = tworound(collisionX - EPSILON);
                ASSERT(tworound(result) == above);
                ASSERT(tworound(result) == beyond);
                result = collisionY;
                above = tworound(collisionY + EPSILON);
                beyond = tworound(collisionY - EPSILON);
                ASSERT(tworound(result) == above);
                ASSERT(tworound(result) == beyond);
            }                   /*eob */
#endif                          /*def DEBUG */
#ifdef DEBUG
            {
                double leftTime;
                double rightTime;

                leftTime = timeFromPosition(&leftGun, collisionX, collisionY);
                rightTime = timeFromPosition(&rightGun, collisionX, collisionY);
                ASSERT(fabs(leftTime - rightTime) <= MAX_DELAY);
            }                   /*eob */
#endif                          /*def DEBUG */
        }
        else
        {
            fprintf(stdout, "Robots do not collide.\n\n");
        }
    }
    return 0;
}
