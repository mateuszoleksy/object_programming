#include <gtest/gtest.h>
#include "../clients/clients.h"

TEST(ClientTest, CreateClient)
{
    Client client("Jan", "Kowalski", "jan@example.com", "123456789", "PESEL123");
    EXPECT_EQ(client.getName(), "Jan");
    EXPECT_EQ(client.getSurname(), "Kowalski");
    EXPECT_EQ(client.getEmail(), "jan@example.com");
}