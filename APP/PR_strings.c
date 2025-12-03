/*******************************************************************************************************************************//**
 * @details		Proyecto: TK18103-3 Estaciones
 * @file		PR_strings.c
 * @brief		DESCRIPCION ---------------
 * @date		31/10/2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <PR_Strings.h>
#include <stdarg.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define     LEYENDA         0
#define     FORMATO         1

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
char Mensaje0 [20];
char Mensaje1 [20];

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
void Sprintf(char* buff , char *formato, ...) {

    char *p,*q , aux[30],relleno;
    int val , j , Estado = LEYENDA , caracteres;


    va_list pa;

    va_start(pa, formato);

    for ( p = formato ; *p ;  )
    {
        switch ( Estado )
        {
            case LEYENDA:
                if (*p != '%')
                {
                    *buff = *p;
                    buff++;
                    p++;
                }
                else
                {
                    if(*( p + 1 ) == '%')
                    {
                        *buff = *p;
                        buff++;
                        p++;
                    }
                    else
                        Estado = FORMATO ;
                    p++;
                }
                break;

            case FORMATO:
                switch (*p)
                {
                    case 'd':
                        val = va_arg(pa, int);
                        Itoa( aux , val );
                        for ( j = 0 ; aux[j] ; j++ )
                        {
                            *buff = aux[ j ];
                            buff++;
                        }
                        p++;
                        break;
                    case 'x':
                        val = va_arg(pa, int);
                        Htoa( aux , val );
                        for ( j = 0 ; aux[j] ; j++ )
                        {
                            *buff = aux[ j ];
                            buff++;
                        }
                        p++;
                        break;
                    case 'b':
                        val = va_arg(pa, int);
                        Btoa( aux , val );
                        for ( j = 0 ; aux[j] ; j++ )
                        {
                            *buff = aux[ j ];
                            buff++;
                        }
                        p++;
                        break;
                    case 'c':
                        val = va_arg(pa, int );
                        *buff = (char) val;
                        buff++;
                        p++;
                        Estado = LEYENDA ;

                        break;
                    case 's':
                        q = va_arg(pa, char *);

                        while ( *q )
                        {
                            *buff = *q;
                            buff++;q++;
                        }
                        p++;
                        Estado = LEYENDA ;

                        break;
                    default:
                        if ( *(p+1) >= '0' && *(p+1) <= '9')
                        {
                            relleno = *p;
                            caracteres = *( p + 1 ) - '0';
                            if ( *( p + 2 ) == 'd' || *( p + 2 ) == 'x'|| *( p + 2 ) == 'b')
                            {
                                val = va_arg(pa, int);
                                switch ( *( p + 2 ) )
                                {
                                    case 'd':
                                        Itoa( aux , val );
                                        break;
                                    case 'x':
                                        Htoa( aux , val );
                                        break;
                                    case 'b':
                                        Btoa( aux , val );
                                        break;
                                }

                                Strformat(aux,relleno,caracteres);

                                for ( j = 0 ; aux[j] ; j++ )
                                {
                                    *buff = aux[ j ];
                                     buff++;
                                }
                                p++;p++;p++;
                            }
                            Estado = LEYENDA ;
                        }
                        else
                        {
                            if ( *p >= '0' && *p <= '9')
                            {
                                caracteres = *( p ) - '0';
                                if ( *( p + 1 ) == 'd' || *( p + 1 ) == 'x'|| *( p + 1 ) == 'b' )
                                {
                                     val = va_arg(pa, int);

                                     switch ( *( p + 1 ) )
                                     {
                                         case 'd':
                                             Itoa( aux , val );
                                             break;
                                         case 'x':
                                             Htoa( aux , val );
                                             break;
                                         case 'b':
                                             Btoa( aux , val );
                                             break;
                                    }

                                    Strformat( aux , ' ' , caracteres );

                                    for ( j = 0 ; aux[j] ; j++ )
                                    {
                                        *buff = aux[ j ];
                                        buff++;
                                    }
                                    p++;p++;

                                }
                                Estado = LEYENDA ;
                            }
                            else
                                Estado = LEYENDA ;
                        }
                        break;
                }
            }
    }

    *buff = '\x0';
}


/**
	@fn  		void Itoa( char* str, int32_t Val )
	@brief 		convierte un entero en un string
 	@author 	Ing. Marcelo Trujillo
 	@date 		25/10/17
 	@param 		[out] string: direcion de comienzo de la string eb�n donde se deja el dato convertido
 	@param 		[in ] Val: valor a convertir
	@return void
*/
void Itoa( char* str, int32_t Val )
{
	uint8_t i = 0 , j ;
	char aux [20] , signo = 0,k;

	if ( Val < 0 )
	{
		signo = '-';
		Val = -Val;
	}

	do
	{
		aux[ i ] = '0' + Val % 10;
		Val /= 10;
		i ++;
	}
	while ( Val );

	aux[i] = '\0';

	k = j = 0;

	if ( signo == '-')
	{
		str[0] = '-';
		j = 1;
		k = 1;
	}

	for ( ; j < (i + k ); j++ )
		str[j] = aux[i + k - j - 1];
	str[j] = '\0';
}

/**
    @fn  		void Btoa( char* str, int32_t Val )
    @brief 		convierte un entero en un string representado por bits
    @author 	Ing. Marcelo Trujillo
    @date 		25/10/17
    @param 		[out] string: direcion de comienzo de la string eb�n donde se deja el dato convertido
    @param 		[in ] Val: valor a convertir
    @return void
*/
void Btoa( char* str, int32_t Val )
{
    uint8_t  i = 0 , j ;
    char aux [20] , k;
    do
    {
        aux[ i ] = '0' + Val % 2;
        Val /= 2;
        i ++;
    }
    while ( Val );

    aux[i] = '\0';

    k = j = 0;

    for ( ; j < (i + k ); j++ )
        str[j] = aux[i + k - j - 1];
    str[j] = '\0';
}
/**
    @fn  		void Htoa( char* str, int32_t Val )
    @brief 		convierte un hexa en un string
    @author 	Ing. Marcelo Trujillo
    @date 		25/10/17
    @param 		[out] string: direcion de comienzo de la string eb�n donde se deja el dato convertido
    @param 		[in ] Val: valor a convertir
    @return void
*/
void Htoa( char* str, int Val )
{
    unsigned char  i = 0 , j ;
    char aux [20] , signo = 0,k;

    if ( Val < 0 )
    {
        signo = '-';
        Val = -Val;
    }

    do
    {
        k = Val % 16;
        if ( k >= 0 && k <= 9 )
            aux[ i ] = '0' + k ;
        else
            aux[ i ] = 'a' + k - 10;

        Val /= 16;
        i ++;
    }
    while ( Val );

    aux[i] = '\0';

    k = j = 0;

    if ( signo == '-')
    {
        str[0] = '-';
        j = 1;
        k = 1;
    }

    for ( ; j < (i + k ); j++ )
        str[j] = aux[i + k - j - 1];
    str[j] = '\0';
}
/**
	@fn  		void Strcat ( char* d , char* o )
	@brief 		concatena dos strings d + o
 	@author 	Ing. Marcelo Trujillo
 	@date 		25/10/17
 	@param 		[out] d: destino de la concatenacion
 	@param 		[in ] o: origen de la string a concatenar
	@return void
*/
void Strcat ( char* d , char* o )
{
	uint8_t i = 0 , j = 0;

	while ( d [ i ] )
		i++;

	while ( o [ j ] )
	{
		d [ i ] = o [ j ];
		i++;
		j++;
	}
	d [ i ] = o [ j ];
}

/**
	@fn  		void Strcpy ( char* d , char* o )
	@brief 		Copia una string sobre otra
 	@author 	Ing. Marcelo Trujillo
 	@date 		25/10/17
 	@param 		[out] d: destino de la copia
 	@param 		[in ] o: fuente de la copia
	@return void
*/
void Strcpy ( char* d , char* o )
{
	uint8_t i = 0;

	while ( o [ i ] )
	{
		d [ i ] = o [ i ];
		i++;
	}
	d [ i ] = o [ i ];
}

/**
	@fn  		int16_t  Strcmp ( const char* s1 , const char* s2 )
	@brief 		Compara dos strings
 	@author 	Ing. Marcelo Trujillo
 	@date 		25/10/17
 	@param 		[ in ] s1: Sring a comparar
 	@param 		[ in ] s2: string a comparar
	@return void
*/
int16_t  Strcmp ( const char* s1 , const char* s2 )
{
	uint8_t i = 0;

	while ( s1 [ i ] != '\0' && s2 [ i ] != '\0')
	{
		if ( s1 [ i ] !=  s2 [ i ])
			return (s1 [ i ] - s2 [ i ]);
		i++;
	}
	return (s1 [ i ] - s2 [ i ]);
}
/**
	@fn  		void Strformat ( char* d , char f , uint8_t n)
	@brief 		Completa al ppio de la string con el caracter enviado en f
 	@author 	Ing. Marcelo Trujillo
 	@date 		25/10/17
 	@param 		[out] d: String a formatear
 	@param 		[in ] f: caracter con el que se completara
 	@param 		[in ] n: tama�o final de la string
	@return void
*/
void Strformat ( char* d , char f , uint8_t n)
{
	uint8_t i = 0 , j ;
	char aux[20];

	while ( d [ i ] )
		i++;

	if ( i >= n )
		return ;

	for (j = 0 ; j < n-i ; j++)
		aux[ j ] = f;
	aux[j] = '\0';

	Strcat ( aux , d );
	Strcpy ( d , aux );
}

