#include "../include/catch.hpp"

#include "../include/string_soma.hpp"
#include "../include/lista_func.hpp"

TEST_CASE ("soma_string" , "algo") {
	SECTION("soma_positiva"){
		REQUIRE (3 == soma_string("1,2\n"));
		REQUIRE (6 == soma_string("1,2,3\n"));
	}
	SECTION("argumento_errado") {/*estao agrupados por terem como resultado -1*/
		SECTION("falta_de_informacao")
			REQUIRE (-1 == soma_string("1,\n"));

		SECTION("iniciar_com_delimitador"){
			REQUIRE (-1 == soma_string(",2\n"));
			REQUIRE (-1 == soma_string(",\n"));
		}
		SECTION("delimitadores_em_sequencia"){
			REQUIRE (-1 == soma_string("1,,2\n"));
		}

		SECTION("delimitador_errado"){
			REQUIRE (-1 == soma_string("1;2\n"));
		}

		SECTION("sem_quebra_de_linha"){
			REQUIRE (-1 == soma_string("1,2"));
		}
		SECTION("caracter_estranho"){
			REQUIRE (-1 == soma_string("1,2 \n"));
		}
		SECTION("numero_negativo"){
			REQUIRE (-1 == soma_string("-1,2\n"));
		}
	}
	SECTION("mais_de_uma_quebra_de_linha") {
		REQUIRE (3 == soma_string("1\n,2\n"));
		REQUIRE (5 == soma_string("1\n\n\n,4\n"));
		REQUIRE (4 == soma_string("1\n\n\n,\n\n\n3\n"));
	}
	SECTION("mais_de_3_numeros") {
		REQUIRE (-1 == soma_string("1,2,3,4\n"));
		REQUIRE (10 == soma_string("1,2,3\n,4\n"));
		SECTION("numero_maior_que_1000"){
			REQUIRE (5 == soma_string("3,2000\n"));
		}
	}
	SECTION("adicao_de_delimitadores") {
		REQUIRE(5 == soma_string("//[;]\n2;3\n"));
		REQUIRE(6 == soma_string("//[**][;;;]\n2**1;;;3\n"));
	}
}