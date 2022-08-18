#include <math.h>
#include <GL/glut.h>


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);

	double radius{ 0.9 };
	double angle{ 0.0 };
	double incrementAngle{ 0.0 };
	int numOfSides{ 5 };
	int numOfLines{ 50 };

	/*std::cout << "Enter the number of sides: ";
	std::cin >> numOfSides;
	std::cout << "Enter number of lines to interpolate: ";
	std::cin >> numOfLines; */

	incrementAngle = 2 * M_PI / numOfSides;

	for (int i = 0; i < numOfSides; i++)
	{
		// NOTE: cos() and sin() are calculated in radians not degrees
		// These lines draw in blue from the center to each vertex to form triangles
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(radius * cos(angle), radius * sin(angle));

		// These lines draw a polygon around the center depending on the number of lines input
		glColor3f(1.0, 0.0, 1.0);
		glVertex2f(radius * cos(angle), radius * sin(angle));

		//increment the angle to draw the next line from the end of the previous point
		angle += incrementAngle;
		glVertex2f(radius * cos(angle), radius * sin(angle));

		// Create another loop to interpolate lines
		for (double k = 0.0; k <= numOfLines; k++)
		{
			double kDividedNumOfLines = k / numOfLines;
			double radTimesSin = radius * sin(angle);
			double radTimesCos = radius * cos(angle);
			
			double radTimesSinPlusAngle = radius * sin(angle + incrementAngle);
			double radTimesCosPlusAngle = radius * cos(angle + incrementAngle);

			// Green Lines
			// Derived from (1 - t) * a + t * b where a = x and b = y
			glColor3f(0.0, 1.0, 0.5);
			glVertex2f(kDividedNumOfLines * radTimesCos, kDividedNumOfLines * radTimesSin);
			glVertex2f((1 - kDividedNumOfLines) * radTimesCos + kDividedNumOfLines * radTimesCosPlusAngle, (1 - kDividedNumOfLines) * radTimesSin + kDividedNumOfLines * radTimesSinPlusAngle);
			

			// Yellow lines
			// TODO: Understand the rotation of polygon and correctly set it in line with rest of figure
			glColor3f(1.0, 1.0, 0.0);
			glVertex2f((1 - kDividedNumOfLines) * radTimesSin + kDividedNumOfLines * radTimesSinPlusAngle, (1 - kDividedNumOfLines) * radTimesCos + kDividedNumOfLines * radTimesCosPlusAngle);
			glVertex2f(kDividedNumOfLines * radTimesSin, kDividedNumOfLines * radTimesCos);
		}		
	}

	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Line Art");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
