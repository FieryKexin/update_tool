TEMP_DIR="/Users/zkxin/Desktop/project/update_tool/download_file"
RELEASE_DIR="/Users/zkxin/Desktop/project/update_tool/3dlogi"

unzip -o $TEMP_DIR/download_latest_version.zip -d $TEMP_DIR/

/bin/cp –rf $TEMP_DIR/3dfinder/Project3DFinder $RELEASE_DIR/
/bin/cp –rf $TEMP_DIR/3dfinder/lib/* $RELEASE_DIR/lib
rm -r $TEMP_DIR/*
