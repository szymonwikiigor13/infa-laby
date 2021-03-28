#include "image.h"
#include "db.h"

int main() {
	ImageDb* db = new_db();

	PgmImage* img1 = new_img(8, 8, 10);
	PgmImage* img2 = new_img(9, 3, 12);

	add_to_db(db, img1);
	add_to_db(db, img2);

	print_db(db);

	PgmImage* ref1 = get_from_db(db, 1);
	print_img(ref1);

	delete_from_db(db, 0);
	print_db(db);

	PgmImage* img3 = new_img(3, 9, 9);
	print_img(img3);

	set_in_db(db, img3, 0);
	print_db(db);

	delete_db(db);
}
