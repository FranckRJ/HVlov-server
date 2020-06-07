#include <catch2/catch.hpp>

#include "Url.hpp"

using namespace hvlov;

SCENARIO("Url::toString()", "[unit]")
{
    GIVEN("A constructed URL from a string")
    {
        std::string urlAsString = "something";
        Url url{urlAsString};

        WHEN("The toString() method is called")
        {
            const std::string& returnedString = url.toString();

            THEN("A copy of the URL passed as parameter of the constructor is returned")
            {
                REQUIRE(returnedString == urlAsString);
                REQUIRE(&returnedString != &urlAsString);
            }
        }

        WHEN("The toString() method is called multiple times")
        {
            const std::string& firstReturnedString = url.toString();
            const std::string& secondReturnedString = url.toString();

            THEN("Each call return a different string (but with the same value)")
            {
                REQUIRE(firstReturnedString == secondReturnedString);
                REQUIRE(&firstReturnedString != &secondReturnedString);
            }
        }
    }
}

SCENARIO("Url::operator<=>()", "[unit]")
{
    GIVEN("Two URL constructed from the same string")
    {
        std::string urlAsString = "something";
        Url firstUrl{urlAsString};
        Url secondUrl{urlAsString};

        WHEN("They are compared")
        {
            THEN("They are equals")
            {
                REQUIRE(firstUrl == secondUrl);
                REQUIRE_FALSE(firstUrl != secondUrl);
            }
        }
    }

    GIVEN("Two URL constructed from two non-equals strings")
    {
        std::string firstUrlAsString = "something";
        std::string secondUrlAsString = "other_thing";
        Url firstUrl{firstUrlAsString};
        Url secondUrl{secondUrlAsString};

        WHEN("They are compared")
        {
            THEN("They are not equals")
            {
                REQUIRE(firstUrl != secondUrl);
                REQUIRE_FALSE(firstUrl == secondUrl);
            }
        }
    }
}
