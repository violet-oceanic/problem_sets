import csv
import sys



def main():
    #databases = "databases/small.csv"
    #sequences = "sequences/1.txt"
    
    # TODO: Check for command-line usage
    if len(sys.argv) == 3:
        databases = sys.argv[1]
        sequences = sys.argv[2]
    else:
        print("Incorrect arguments being passed")
        exit()

    # TODO: Read database file into a variable
    rows = []
    with open(databases) as file:
        db_reader = csv.DictReader(file)
        field_count = len(db_reader.fieldnames)
        for row in db_reader:
            rows.append(row)
    
    # TODO: Read DNA sequence file into a variable
    with open(sequences) as file:
        sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    matches = {}
    for i in range(1,field_count):
        matches[db_reader.fieldnames[i]] = longest_match(sequence, db_reader.fieldnames[i])


    # TODO: Check database for matching profiles
    for row in rows:
        match_count = 0
        for match in matches:
            if int(row[match]) == matches[match]:
                match_count += 1
        
        if match_count == len(matches):
            print(row['name'])
            exit()

    print("No match.")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

