#include "spreadsheet.hpp"
#include "spreadsheet.cpp"
#include "select.hpp"
#include "gtest/gtest.h"


TEST(SelectContains, FullList) {
	Spreadsheet s;
	s.set_column_names({ "First", "Last", "Major" });
	s.add_row({ "Jerry", "Smith", "English" });
	s.add_row({ "Peter", "Pan", "Math" });
	s.add_row({ "Abhi", "Patel", "CS" });
	s.add_row({ "Ian", "Lee", "Biology" });
	s.add_row({ "Joe", "Cook", "Engineering" });
	std::stringstream out;
	s.print_selection(out);
	EXPECT_EQ("Jerry Smith English \nPeter Pan Math \nAbhi Patel CS \nIan Lee Biology \nJoe Cook Engineering \n", out.str());
}

TEST(SelectContains, PassedRows) {
	Spreadsheet s;
	s.set_column_names({ "First", "Last", "Major" });
	s.add_row({ "Jerry", "Smith", "English" });
	s.add_row({ "Peter", "Pan", "Math" });
	s.add_row({ "Abhi", "Patel", "CS" });
	s.add_row({ "Ian", "Lee", "Biology" });
	s.add_row({ "Joe", "Cook", "Engineering" });
	std::stringstream out;
	s.set_selection(new Select_Contains(&s, "Major", "F"));
	s.print_selection(out);
	EXPECT_EQ("Peter Pan Math \nIan Lee Biology \n", out.str());

}

TEST(SelectContains, NotInList) {
	Spreadsheet s;
	s.set_column_names({ "First", "Last", "Major" });
	s.add_row({ "Jerry", "Smith", "English" });
	s.add_row({ "Peter", "Pan", "Math" });
	s.add_row({ "Abhi", "Patel", "CS" });
	s.add_row({ "Ian", "Lee", "Biology" });
	s.add_row({ "Joe", "Cook", "Engineering" });
	std::stringstream out;
	s.set_selection(new Select_Contains(&s, "Last", "0"));
	s.print_selection(out);
	EXPECT_EQ("", out.str());

}

TEST(SelectNot, NoCharacter) {
	Spreadsheet s;
	s.set_column_names({ "First", "Last", "Major" });
	s.add_row({ "Jerry", "Smith", "English" });
	s.add_row({ "Peter", "Pan", "Math" });
	s.add_row({ "Abhi", "Patel", "CS" });
	s.add_row({ "Ian", "Lee", "Biology" });
	s.add_row({ "Joe", "Cook", "Engineering" });
	std::stringstream out;
	s.set_selection(new Select_Not(new Select_Contains(&s, "First", "a")));
	s.print_selection(out);
	EXPECT_EQ("Abhi Patel CS \nJoe Cook Engineering \n", out.str());

}

TEST(SelectNot, TwoChars) {
	Spreadsheet s;
	s.set_column_names({ "First", "Last", "Major" });
	s.add_row({ "Jerry", "Smith", "English" });
	s.add_row({ "Peter", "Pan", "Math" });
	s.add_row({ "Abhi", "Patel", "CS" });
	s.add_row({ "Ian", "Lee", "Biology" });
	s.add_row({ "Joe", "Cook", "Engineering" });
	std::stringstream out;
	s.set_selection(new Select_Not(new Select_Contains(&s, "Last", "Ka")));
	s.print_selection(out);
	EXPECT_EQ("Jerry Smith English \nPeter Pan Math \nAbhi Patel CS \nIan Lee Biology \nJoe Cook Engineering \n", out.str());

}

TEST(SelectAnd, ContainNot) {
	Spreadsheet s;
	s.set_column_names({ "First", "Last", "Major" });
	s.add_row({ "Jerry", "Smith", "English" });
	s.add_row({ "Peter", "Pan", "Math" });
	s.add_row({ "Abhi", "Patel", "CS" });
	s.add_row({ "Ian", "Lee", "Biology" });
	s.add_row({ "Joe", "Cook", "Engineering" });
	std::stringstream out;
	s.set_selection(new Select_And(
		new Select_Contains(&s, "Major", "n"),
		new Select_Not(new Select_Contains(&s, "Major", "o"))));
	s.print_selection(out);
	EXPECT_EQ("Jerry Smith English \nPeter Pan Math \n", out.str());

}

TEST(SelectAnd, ContainsBothSame) {
	Spreadsheet s;
	s.set_column_names({ "First", "Last", "Major" });
	s.add_row({ "Jerry", "Smith", "English" });
	s.add_row({ "Peter", "Pan", "Math" });
	s.add_row({ "Abhi", "Patel", "CS" });
	s.add_row({ "Ian", "Lee", "Biology" });
	s.add_row({ "Joe", "Cook", "Engineering" });
	std::stringstream out;
	s.set_selection(new Select_And(
		new Select_Contains(&s, "First", "a"),
		new Select_Contains(&s, "First", "r")));
	s.print_selection(out);
	EXPECT_EQ("Peter Pan Math \nIan Lee Biology \n", out.str());

}

TEST(SelectAnd, ContainsBoth) {
	Spreadsheet s;
	s.set_column_names({ "First", "Last", "Major" });
	s.add_row({ "Jerry", "Smith", "English" });
	s.add_row({ "Peter", "Pan", "Math" });
	s.add_row({ "Abhi", "Patel", "CS" });
	s.add_row({ "Ian", "Lee", "Biology" });
	s.add_row({ "Joe", "Cook", "Engineering" });
	std::stringstream out;
	s.set_selection(new Select_And(
		new Select_Contains(&s, "First", "a"),
		new Select_Contains(&s, "Last", "d")));
	s.print_selection(out);
	EXPECT_EQ("Jerry Smith English \nIan Lee Biology \n", out.str());

}

TEST(SelectOr, Either) {
	Spreadsheet s;
	s.set_column_names({ "First", "Last", "Major" });
	s.add_row({ "Jerry", "Smith", "English" });
	s.add_row({ "Peter", "Pan", "Math" });
	s.add_row({ "Abhi", "Patel", "CS" });
	s.add_row({ "Ian", "Lee", "Biology" });
	s.add_row({ "Joe", "Cook", "Engineering" });
	std::stringstream out;
	s.set_selection(new Select_Or(
		new Select_Contains(&s, "First", "o"),
		new Select_Contains(&s, "Last", "n")));
	s.print_selection(out);
	EXPECT_EQ("Jerry Smith English \nPeter Pan Math \nAbhi Patel CS \nJoe Cook Engineering \n", out.str());

}

TEST(SelectOr, TwoOr) {
	Spreadsheet s;
	s.set_column_names({ "First", "Last", "Major" });
	s.add_row({ "Jerry", "Smith", "English" });
	s.add_row({ "Peter", "Pan", "Math" });
	s.add_row({ "Abhi", "Patel", "CS" });
	s.add_row({ "Ian", "Lee", "Biology" });
	s.add_row({ "Joe", "Cook", "Engineering" });
	std::stringstream out;
	s.set_selection(new Select_Or(
		new Select_Contains(&s, "First", "br"),
		new Select_Or(
			new Select_Contains(&s, "Last", "n"),
			new Select_Contains(&s, "Major", "ee"))));
	s.print_selection(out);
	EXPECT_EQ("Jerry Smith English \nAbhi Patel CS \nIan Lee Biology \nJoe Cook Engineering \n", out.str());
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
