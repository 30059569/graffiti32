#ifndef __GRAFFITI32_GRAFFITI_H__
#define __GRAFFITI32_GRAFFITI_H__

#include <math.h>
#include <windows.h>

#define COVER_TRESHOLD 6
#define INTERLIEVE_GRANULARITY 64

#define CHAR_LEFT    (char)0
#define CHAR_RIGHT   (char)1
#define CHAR_OPTION  '/'
#define CHAR_BACK    '\b'
#define CHAR_TAB     '\t'
#define CHAR_ENTER   '\n'
#define CHAR_SPACE   ' '



template<class T> class List {
	long size;
	long inc;

public:
	long count;
	T * list;

	List(long initialSize, long incrementBy) {
		size = initialSize;
		inc = incrementBy;
		count = 0;
		list = (T*) malloc(sizeof(T) * size);
	}
	~List() {
		free(list);
	}

	void add(T * point) {
		if (point) {
			if (count >= size) {
				size += inc;
				list = (T*) realloc(list, sizeof(T) * size);
			}
			memcpy(list + count, point, sizeof(T));
			count++;
		}
	}
};

typedef struct {
	char letter;
	long size;
	POINT points[10];
} TLeterInfo;

class NormalizedLetter {

public:

	double* letterxInterpol;
	double* letteryInterpol;

	char letter;

	NormalizedLetter(long size, POINT points[]) {
		processLetter(size, points);
	}

	NormalizedLetter(TLeterInfo& letterInfo) {
		processLetter(letterInfo.size, letterInfo.points);
		letter = letterInfo.letter;
	}

	void processLetter(long size, POINT points[]) {
		letterxInterpol = new double[INTERLIEVE_GRANULARITY];
		letteryInterpol = new double[INTERLIEVE_GRANULARITY];

		double* letterxNorm = new double[size];
		double* letteryNorm = new double[size];
		double* length = new double[size];

		letter = '\0';

		double minx = points[0].x;
		double miny = points[0].y;
		double maxx = minx;
		double maxy = miny;

		for (int i = 1; i < size; i++) {
			const int letterX = points[i].x;
			if (letterX < minx) {
				minx = letterX;
			}
			if (letterX > maxx) {
				maxx = letterX;
			}

			const int letterY = points[i].y;
			if (letterY < miny) {
				miny = letterY;
			}
			if (letterY > maxy) {
				maxy = letterY;
			}
		}

		const double dx = maxx - minx;
		const double dy = maxy - miny;

		if (dx + dy < 6.0) {
			letter = '.';
		} else if (maxy == miny || dx / dy > 6.0) {
			letter = '-';
		} else if (maxx == minx || dy / dx > 6.0) {
			letter = '|';
		}

		// initialize letterxNorm and letteryNorm arrays
		// letterxNorm and letteryNorm are normalized versions 
		// 		(values from 0 to 1) with 0 being a bit sticky ;-)
		for (int i = 0; i < size; i++) {
			if (letter == '|' || letter == '.') {
				letterxNorm[i] = 0.0F;
			} else {
				letterxNorm[i] = ((double) (points[i].x) - minx) / dx;
			}
			if (letter == '-' || letter == '.') {
				letteryNorm[i] = 0.0F;
			} else {
				letteryNorm[i] = ((double) (points[i].y) - miny) / dy;
			}
		}

		// initialize length
		// length represents the accumulated length of the segments
		length[0] = 0.0F;
		for (int i = 1; i < size; i++) {
			length[i] = length[i - 1] + sqrt((letterxNorm[i] - letterxNorm[i
					- 1]) * (letterxNorm[i] - letterxNorm[i - 1])
					+ (letteryNorm[i] - letteryNorm[i - 1]) * (letteryNorm[i]
							- letteryNorm[i - 1]));
		}

		// interpolate letterxNorm and letteryNorm to have subDivisionMax 
		// definition points for each letter.

		int index;
		const double totalLength = length[size - 1];
		for (int subDivisionIndex = 0; subDivisionIndex
				< INTERLIEVE_GRANULARITY; subDivisionIndex++) {
			// find the index of the first point after "percentage" of the path			
			const double percentage = ((double) subDivisionIndex
					/ (double) (INTERLIEVE_GRANULARITY - 1));
			const double percentageLength = totalLength * percentage;
			for (index = 1; length[index] < percentageLength; index++)
				;

			// security check
			if (index > size - 1) {
				index = size - 1;
			}

			const double dlen = length[index] - length[index - 1];
			if (dlen == 0.0) {
				letterxInterpol[subDivisionIndex] = letterxNorm[index];
				letteryInterpol[subDivisionIndex] = letteryNorm[index];
			} else {
				const double f3 = (length[index] - percentageLength) / dlen;
				// letterxInterpol and letteryInterpol are interpolations of letterxNorm and letteryNorm
				letterxInterpol[subDivisionIndex] = ((f3) * letterxNorm[index
						- 1]) + ((1.0 - f3) * letterxNorm[index]);
				letteryInterpol[subDivisionIndex] = ((f3) * letteryNorm[index
						- 1]) + ((1.0 - f3) * letteryNorm[index]);
			}
		}

		delete[] letterxNorm;
		delete[] letteryNorm;
		delete[] length;
	}

	~NormalizedLetter() {
		delete[] letterxInterpol;
		delete[] letteryInterpol;
	}

	double distance(NormalizedLetter* rl, double threshold) {
		double distance = 0.0;
		for (int i = 0; i < INTERLIEVE_GRANULARITY; i++) {
			const double dx = letterxInterpol[i] - rl->letterxInterpol[i];
			const double dy = letteryInterpol[i] - rl->letteryInterpol[i];

			distance += dx * dx + dy * dy;
			if (distance > threshold) {
				break;
			}
		}
		return distance;
	}
};

typedef NormalizedLetter* PNormalizedLetter;

class Recognizer {
	PNormalizedLetter* letters;
	PNormalizedLetter* numbers;
	long lettersSize;
	long numbersSize;

	bool DOT_MODE;
	char * DOT_CHARACTER;

public:

	NormalizedLetter* lastLetter;
	NormalizedLetter* lastFoundLetter;

	Recognizer(PNormalizedLetter letters[], long lettersSize,
			PNormalizedLetter numbers[], long numbersSize,
			char * dotTranslationAZ) {
		this->letters = letters;
		this->lettersSize = lettersSize;
		this->numbers = numbers;
		this->numbersSize = numbersSize;
		DOT_MODE = false;
		DOT_CHARACTER = dotTranslationAZ;
		lastLetter = NULL;
		lastFoundLetter = NULL;
	}

	char recognize(const List<POINT>* in, int separator) {
		int minx = in->list[0].x;
		int miny = in->list[0].y;
		int maxx = minx;
		int maxy = miny;

		for (int i = 1, len = in->count; i < len; i++) {
			const int letterX = in->list[i].x;
			if (letterX < minx)
				minx = letterX;
			if (letterX > maxx)
				maxx = letterX;

			const int letterY = in->list[i].y;
			if (letterY < miny)
				miny = letterY;
			if (letterY > maxy)
				maxy = letterY;
		}

		char result = '\0';
		if ((maxx - minx) + (maxy - miny) < COVER_TRESHOLD) {
			result = '.';
		} else if (maxy == miny || (maxx - minx) / (maxy - miny)
				> COVER_TRESHOLD) {
			result = in->list[0].x == minx ? ' ' : CHAR_BACK;
		} else if (maxx == minx || (maxy - miny) / (maxx - minx)
				> COVER_TRESHOLD) {
			result = in->list[0].y == miny ? 'i' : 'I';
		} else {
			if (separator < minx) {
				result = recognizeNumber(in->count, in->list);
			} else {
				result = recognizeAlfa(in->count, in->list);
			}
		}

		if (separator < minx) {
			if (result == CHAR_BACK)
				result = '-';
			else if (result == 'i' || result == 'I' || result == '|')
				result = '1';
		}

		// apply dots mode
		if (!DOT_MODE && result == '.') {
			DOT_MODE = true;
			result = 0;
		} else if (DOT_MODE) {
			if (result == CHAR_ENTER) {
				result = '\\';
			} else if (result == CHAR_SPACE) {
				result = '-';
			} else if (result == '(') {
				result = '[';
			} else if (result == ')') {
				result = ']';
			} else if (result == '/') {
				result = ',';
			} else if (result == 'i') {
				result = '|';
			} else if (result >= 'A' && result <= 'Z') {
				result = DOT_CHARACTER[result - 'A'];
			}
			DOT_MODE = false;
		}

		// lower case if necessary
		if (separator >= maxx && result >= 'A' && result <= 'Z' && result
				!= 'I') {
			result += 0x20;
		}
		return result;
	}

protected:

	char recognizeFrom(long size, POINT points[],
			PNormalizedLetter normalizations[], int normalizedSize) {
		if (lastLetter) {
			delete lastLetter;
		}
		lastLetter = new NormalizedLetter(size, points);

		int minIndex = 0;
		double distance = normalizations[0]->distance(lastLetter,
				INTERLIEVE_GRANULARITY * INTERLIEVE_GRANULARITY);
		double threshhold = distance;
		for (int i = 1; i < normalizedSize; i++) {
			double currentDistance = normalizations[i]->distance(lastLetter,
					threshhold);
			if (currentDistance < distance) {
				distance = currentDistance;
				minIndex = i;
			}
		}
		lastFoundLetter = normalizations[minIndex];
		return lastFoundLetter->letter;
	}

	char recognizeAlfa(long size, POINT points[]) {
		return recognizeFrom(size, points, letters, lettersSize);
	}

	char recognizeNumber(long size, POINT points[]) {
		return recognizeFrom(size, points, numbers, numbersSize);
	}
};

typedef Recognizer* PRecognizer;

#endif
