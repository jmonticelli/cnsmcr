/*****************************************************************************\
 * cnsmcr - Consume a core!
 *
 * Consume a core by nicing this program. Intended to provide some way of
 * handicapping a core.
 *
 * (C) 2019 Julian Monticelli
\*****************************************************************************/

#include <cctype>
#include <cerrno>
#include <cstdlib>

#include <chrono>
#include <iostream>
#include <thread>

int exit_with_help()
{
    char const *program_help =
        "                 ___ _ __  ___ _ __ ___   ___ _ __ \n"
        "                / __| '_ \\/ __| '_ ` _ \\ / __| '__|\n"
        "               | (__| | | \\__ \\ | | | | | (__| |\n"
        "                \\___|_| |_|___/_| |_| |_|\\___|_|\n\n"
        "                   (C) 2019 Julian Monticelli\n"
        "\n"
        "cnsmcr requires a CPU percentage approximation (0.1-100%) in order to run.\n"
        "Remember to nice the process for best results.";
    std::cerr << program_help << std::endl;
    return 0; // help menu isn't... necessarily an error?
}

int error_out_of_range()
{
    std::cerr << "The second argument MUST be a number from 0.1-100" << std::endl;
    return 2;
}

int main(int argc, char **argv)
{

    if (argc == 1)
    {
        return exit_with_help();
    }

    char *err_char;
    errno = 0;
    double const consumption_percentage = std::strtod(argv[1], &err_char);

    if (*err_char != '\0' || errno != 0)
    {
        return exit_with_help();
    }

    if (consumption_percentage > 100.0 || consumption_percentage < 0.1)
    {
        return error_out_of_range();
    }

    double const unscaled_consumption_ratio = consumption_percentage / 100.0;
    auto const max_duration = std::chrono::microseconds(
            static_cast<size_t>(unscaled_consumption_ratio * 1000.0 * 1000.0));

    std::cout << "max_duration = " << max_duration.count() << "microseconds" << std::endl;

    auto last_start = std::chrono::steady_clock::now();
    size_t a_number_to_increment = 0u;
    size_t number_of_jennies = 0u;

    size_t const jenny = 8675309u;


    while (true)
    {
        if (++a_number_to_increment == jenny)
        {
            ++number_of_jennies;
            a_number_to_increment = 0u;
        }

        const auto ran_for_s = (std::chrono::steady_clock::now() - last_start);

        if (ran_for_s >= max_duration && unscaled_consumption_ratio < 100.0f)
        {
            auto const sleepy_time = std::chrono::seconds(1) - ran_for_s;
            std::this_thread::sleep_for(sleepy_time);
            last_start = std::chrono::steady_clock::now();
        }
    }

    return 0; // we'll never get here, but it's nice to dream
}


