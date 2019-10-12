import time

fileName = "5.Infected"

chartFile = open("songs/" + fileName +"/notes.chart","r");

chartsFileList = []


for line in chartFile:

    chartsFileList.append(line)


def adjust(lower,threshold,adjustment):
    newChartsFile = open("songs/" + fileName + "/notes.chart","w")
    startRead = False
    for line in range(len(chartsFileList)):
        if(startRead):
            timing = chartsFileList[line].split(" ")[0]
            try:
                timing = int(timing)
                if(timing < threshold and timing > lower):
                    timing = timing+adjustment
                    chartsFileList[line] = ("\t") + str(timing) +(" ") + chartsFileList[line].split(" ")[1] +(" ") + chartsFileList[line].split(" ")[2] +(" ") + chartsFileList[line].split(" ")[3] +(" ") + chartsFileList[line].split(" ")[4]

            except ValueError:
                print("Error")

        if(chartsFileList[line][:7] == "[Expert"):
            startRead=True
        if(startRead):
            print(chartsFileList[line])
            #time.sleep(0.01)
        newChartsFile.write(chartsFileList[line])
    newChartsFile.close()





chartsFileList = adjust(53000,150000,-240)
